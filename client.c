#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

#define MAX_CHUNK_SIZE 1000
#define MAX_CHUNKS 10
#define SERVER_IP "127.0.0.1" // Server IP address
#define SERVER_PORT 12345     // Server port

// Struct to represent a data chunk
struct DataChunk
{
    int sequence_number;
    char data[MAX_CHUNK_SIZE];
};

// Function to simulate random ACK skipping
int shouldSkipAck()
{
    return rand() % 3 == 0; // Skip every third ACK (for testing)
}

// Function to send data chunks to the server
void sendDataChunks(int sockfd, struct sockaddr_in server_addr, int num_chunks)
{
    for (int i = 0; i < num_chunks; i++)
    {
        struct DataChunk chunk;
        chunk.sequence_number = i;

        // Accept user input for data content
        printf("Enter data for Chunk %d (up to %d characters): ", i, MAX_CHUNK_SIZE);
        fgets(chunk.data, sizeof(chunk.data), stdin);

        // Remove newline character from input
        chunk.data[strcspn(chunk.data, "\n")] = '\0';

        // Send the chunk
        socklen_t server_len = sizeof(server_addr);
        sendto(sockfd, &chunk, sizeof(chunk), 0, (struct sockaddr *)&server_addr, server_len);

        printf("Sent Chunk %d: %s\n", chunk.sequence_number, chunk.data);

        // // Simulate ACK randomization (comment out for final submission)
        // if (!shouldSkipAck())
        // {
        //     int ack;
        //     socklen_t server_len = sizeof(server_addr);

        //     // Receive ACK for the sent chunk
        //     int bytes_received = recvfrom(sockfd, &ack, sizeof(ack), 0, (struct sockaddr *)&server_addr, &server_len);

        //     if (bytes_received == sizeof(ack))
        //     {
        //         printf("Received ACK for Chunk %d\n", ack);
        //     }
        //     else
        //     {
        //         printf("Error receiving ACK for Chunk %d\n", chunk.sequence_number);
        //     }
        // }

        usleep(100000); // Sleep for 0.1 seconds between sending chunks (simulating retransmission delay)
    }
}

int main()
{
    int sockfd;
    struct sockaddr_in server_addr;
    int num_chunks;

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
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    srand(time(NULL)); // Seed for random ACK skipping

    // Accept user input for the number of chunks
    printf("Enter the number of chunks to send: ");
    scanf("%d", &num_chunks);

    // Clear the input buffer
    while (getchar() != '\n')
        ;

    // Send data chunks to the server
    sendDataChunks(sockfd, server_addr, num_chunks);

    close(sockfd);
    return 0;
}
