# REPORT - NETWORKS PART B

## Differences from Traditional TCP
While our aims to mimic some aspects of TCP-like behavior, it lacks the robustness and features of a full TCP implementation.  
The key differences include:

### 1. Connectionless Protocol: 
- UDP is a connectionless protocol, while TCP is a connection-oriented protocol.
   
- In TCP, a connection is established, maintained, and terminated between the sender and receiver. In UDP implementation, there's no three-way handshake, connection setup, or teardown.
  
- UDP thus does not provide the reliability guarantees that TCP offers. 
  
- In traditional TCP, data sequencing and retransmission are built-in features of the protocol. 
  
- In the code in  ```/networks/partB``` , data sequencing and retransmission features are implemented on top of UDP, which is inherently unreliable. Thus, unlike TCP, there is no built-in acknowledgment, etc.

### 2. Randomized ACK Skipping:
- The feature to simulate random ACK skipping that we implemented for testing is not a characteristic of traditional TCP.


### 3. No Guaranteed Delivery:
- UDP traditionally does not guarantee the delivery of data or its order. 
  
- In our code, while we simulate retransmissions for lost packets, UDP itself does not have built-in mechanisms for guaranteed delivery or in-order delivery of packets. 
  
- TCP on the other hand, ensures reliable and ordered delivery of data.

### 4. Checksum and Acknowledgment Handling:
- Both UDP and TCP use checksums to detect errors in transmitted data. TCP on top of that, also includes sequence numbers and acknowledgment numbers to ensure the reliable and ordered delivery of data. 
  
- In our UDP implementation, we include a sequence number. However the acknowledgment handling is much more simplified, and ACK packets are not processed as rigorously as in TCP.

### 5. Retransmission Handling: 
- In our UDP implementation, retransmissions are simulated based on a random skip pattern (every third ACK).

- Traditionally, TCP retransmissions are however triggered based on timeouts and duplicate ACKs. 
  
- TCP uses more sophisticated algorithms, such as the Fast Retransmit and Fast Recovery algorithms, to handle retransmissions effectively.

### 6. No Congestion Control: 
- Traditional TCP includes congestion control mechanisms to adapt to network conditions. 
  
- Our code here however lacks congestion control. This may lead to congestion-related issues in a real-world network.

<br>
<br>

## Extending for Flow Control

### 1. Sender-Side Flow Control:

- Maintain a variable on the sender-side to track the available buffer space at the receiver.
- Before sending a new data chunk, check if there is enough space in the receiver's buffer to accommodate it.
- If there is sufficient space, send the chunk; otherwise, wait until space becomes available.
- Implement a sliding window mechanism to control the number of unacknowledged chunks in flight.
- Maintaining a variable for tracking receiver buffer space is essential. It helps the sender avoid sending data faster than the receiver can process it.

<br>

- Maintain a sliding window of a certain size (e.g., N chunks) at the sender.
- Initially, send the first N chunks.
- Wait for ACKs for these chunks and keep track of the acknowledged sequence numbers.
- As ACKs arrive, slide the window forward and send the next unacknowledged chunk(s).
- Implementing a sliding window mechanism is a good choice, as it allows for fine-grained control over the number of unacknowledged chunks in transit. We can dynamically adjust the window size based on the available buffer space and network conditions.



### 2. Receiver-Side Flow Control:

- The receiver can send ACKs with information about the available buffer space.
- Then we can modify the sender to interpret these ACKs and adjust its sending rate accordingly.
- Then we implement a mechanism for the sender to adaptively adjust the number of chunks it sends based on the receiver's available buffer space.
