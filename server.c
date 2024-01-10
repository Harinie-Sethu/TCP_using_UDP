#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX_CHUNK_SIZE 1000

// Struct to represent a data chunk
struct DataChunk
{
    int sequence_number;
    char data[MAX_CHUNK_SIZE];
};

// Function to receive data chunks from the client
void receiveDataChunks(int sockfd, struct sockaddr_in client_addr, int num_chunks)
{
    struct DataChunk chunks[num_chunks];
    int received_chunks = 0;

    while (received_chunks < num_chunks)
    {
        struct DataChunk chunk;
        socklen_t client_len = sizeof(client_addr);

        // Receive a chunk
        int bytes_received = recvfrom(sockfd, &chunk, sizeof(chunk), 0, (struct sockaddr *)&client_addr, &client_len);

        if (bytes_received == sizeof(chunk))
        {
            // comment out uring simulation
            printf("Received Chunk %d: %s\n", chunk.sequence_number, chunk.data);
            received_chunks++;

            // // Simulate ACK randomization (comment out for final submission)
            // if (chunk.sequence_number % 3 != 0)
            // {
            //     printf("Received Chunk %d: %s\n", chunk.sequence_number, chunk.data);
            //     received_chunks++;
            // }
            // else
            // {
            //     printf("Received Chunk %d (ACK skipped)\n", chunk.sequence_number);
            // }

            // Store the received chunk
            chunks[chunk.sequence_number] = chunk;

            // Send ACK for the received chunk
            sendto(sockfd, &chunk.sequence_number, sizeof(chunk.sequence_number), 0, (struct sockaddr *)&client_addr, client_len);
        }
        else
        {
            printf("Error receiving data chunk.\n");
        }
    }

    // Reassemble and display the complete text
    char complete_text[MAX_CHUNK_SIZE * num_chunks];
    memset(complete_text, 0, sizeof(complete_text));

    for (int i = 0; i < num_chunks; i++)
    {
        strcat(complete_text, chunks[i].data);
    }

    printf("\nComplete Text:\n%s\n", complete_text);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <number_of_chunks>\n", argv[0]);
        exit(1);
    }

    int num_chunks = atoi(argv[1]);

    int sockfd;
    struct sockaddr_in server_addr, client_addr;

    // Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        perror("Error in socket creation");
        exit(1);
    }

    // Initialize server address structure
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(12345); // Choose a port number
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind socket to server address
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Error in binding");
        exit(1);
    }

    printf("Server is running...\n");

    // Receive data chunks and handle ACKs
    receiveDataChunks(sockfd, client_addr, num_chunks);

    close(sockfd);
    return 0;
}
