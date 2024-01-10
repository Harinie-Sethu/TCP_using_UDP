# TCP_using_UDP
Implementation of some functionalities using UDP sockets : Data Sequencing and Retransmissions

## Data Sequencing
The sender (client or server - both should be able to send as well as receive data) must divide the data (assume some text) into smaller chunks (using chunks of fixed size or using a fixed number of chunks). Each chunk is assigned a number which is sent along with the transmission (use structs). The sender should also communicate the total number of chunks being sent [1]. After the receiver has data from all the chunks, it should aggregate them according to their sequence number and display the text.

## Retransmissions
The receiver must send an ACK packet for every data chunk received (The packet must reference the sequence number of the received chunk). If the sender doesn’t receive the acknowledgement for a chunk within a reasonable amount of time (say 0.1 seconds), it must resend the data. However, the sender shouldn’t wait for receiving acknowledgement for a previously sent chunk before transmitting the next chunk.

## Explanation
- client.c and server.c contains the code for this part.
- To run them, open TWO terminals - one for client and one for server.
- cd into ```/networks/partB```
- let n be the number of chunks we want to be sent. You will have to enter this number in both the client and server terminals. Let us take n to be 7 in this case.
  
- In server terminal run:
  ```
  gcc terminal.c
  ./a.out 7
  ```

  ```
  Server is running...
  Received Chunk 0: hi
  Received Chunk 1: this
  Received Chunk 2: is
  Received Chunk 3: me
  Received Chunk 4: lol
  Received Chunk 5: hope
  Received Chunk 6: it

  Complete Text:
  hithisismelolhopeit
  ```
  
- In client A terminal run:
  ```
  gcc client.c
  ./a.out
  ```
  ```
  Enter the number of chunks to send: 7
  Enter data for Chunk 0 (up to 1000 characters): hi
  Sent Chunk 0: hi
  Enter data for Chunk 1 (up to 1000 characters): this
  Sent Chunk 1: this
  Enter data for Chunk 2 (up to 1000 characters): is
  Sent Chunk 2: is
  Enter data for Chunk 3 (up to 1000 characters): me
  Sent Chunk 3: me
  Enter data for Chunk 4 (up to 1000 characters): lol
  Sent Chunk 4: lol
  Enter data for Chunk 5 (up to 1000 characters): hope
  Sent Chunk 5: hope
  Enter data for Chunk 6 (up to 1000 characters): it
  Sent Chunk 6: it
  ```
- report for Part B can be found in the ``networks/partB/reportB.MD``
<br>
<br>

## References:
- Chatgpt for inference and help
- https://nikhilroxtomar.medium.com/tcp-client-server-implementation-in-c-idiot-developer-52509a6c1f59    - ```for TCP```
- https://nikhilroxtomar.medium.com/udp-client-server-implementation-in-c-idiot-developer-c61ce6369352?source=rss-a4782a8f5e78------2          - ```for UDP```
- https://www.scaler.com/topics/udp-server-client-implementation-in-c/    - ```for UDP```
