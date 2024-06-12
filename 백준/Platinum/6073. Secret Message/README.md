# [Platinum V] Secret Message - 6073 

[문제 링크](https://www.acmicpc.net/problem/6073) 

### 성능 요약

메모리: 6884 KB, 시간: 48 ms

### 분류

자료 구조, 트리, 트라이

### 제출 일자

2024년 4월 21일 21:58:17

### 문제 설명

<p>Bessie is leading the cows in an attempt to escape! To do this, the cows are sending secret binary messages to each other.</p>

<p>Ever the clever counterspy, Farmer John has intercepted the first b_i (1 <= b_i <= 10,000) bits of each of M (1 <= M <= 50,000) of these secret binary messages.</p>

<p>He has compiled a list of N (1 <= N <= 50,000) partial codewords that he thinks the cows are using. Sadly, he only knows the first c_j (1 <= c_j <= 10,000) bits of codeword j.</p>

<p>For each codeword j, he wants to know how many of the intercepted messages match that codeword (i.e., for codeword j, how many times does a message and the codeword have the same initial bits).  Your job is to compute this number.</p>

<p>The total number of bits in the input (i.e., the sum of the b_i and the c_j) will not exceed 500,000.</p>

### 입력 

 <ul>
	<li>Line 1: Two integers: M and N</li>
	<li>Lines 2..M+1: Line i+1 describes intercepted code i with an integer b_i followed by b_i space-separated 0's and 1's</li>
	<li>Lines M+2..M+N+1: Line M+j+1 describes codeword j with an integer c_j followed by c_j space-separated 0's and 1's</li>
</ul>

### 출력 

 <ul>
	<li>Lines 1..N: Line j: The number of messages that the jth codeword could match.</li>
</ul>

