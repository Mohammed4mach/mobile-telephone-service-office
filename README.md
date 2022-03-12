# Mobile Telephone Service Office

Simulation of **Mobile Telephone Service Office (MTSO)**, which handle coming calls along with emergency calls.  

## Problem

You can review the problem in [Sheet4.pdf](Sheet4.pdf) file. This sheet from **Data Structures** course introduced by [FCIH OCW](https://www.youtube.com/user/FCIHOCW).  
Read the problem well to understand the solution

## Solution

The problem could be solved by linked-list. But I prefered to make a slight change in the linked-queue design to provide more efficient solution.  
This queue version is just efficient during this problem only.

### Queue Design

Here a diagram that clarify conceptual design of the queue..

![Conceptual queue design diagram](Queue%20Design.jpg)  

*Queue* :
* size : 
  - *integer that hold size of the queue*
* EmergP :
  - *pointing to node of the least prior emergency call among its type*
* VoiceP :
  - *pointing to node of the least prior voice call among its type*
* rear :
  - *pointing to node of the last element in the queue*
* front :
  - *poining to node of the element to be served*  

*Queue Node* :
* entry :
  - *data entry of the node*
* next :
  - *pointing to the next node*
