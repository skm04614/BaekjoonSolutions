# [Gold I] Foehn Phenomena - 14419 

[문제 링크](https://www.acmicpc.net/problem/14419) 

### 성능 요약

메모리: 9840 KB, 시간: 236 ms

### 분류

누적 합

### 제출 일자

2024년 4월 29일 14:08:08

### 문제 설명

<p>In the Kingdom of IOI, the wind always blows from sea to land. There are N + 1 spots numbered from 0 to N. The wind from Spot 0 to Spot N in order. Mr. JOI has a house at Spot N. The altitude of Spot 0 is A<sub>0</sub> = 0, and the altitude of Spot i (1 ≤  i ≤ N) is A<sub>i</sub>.</p>

<p>The wind blows on the surface of the ground. The temperature of the wind changes according to the change of the altitude. The temperature of the wind at Spot 0, which is closest to the sea, is 0 degree. For each i (0 ≤  i ≤ N - 1), the change of the temperature of the wind from Spot i to Spot i + 1 depends only on the values of A<sub>i</sub> and A<sub>i+1</sub> in the following way:</p>

<ul>
	<li>If A<sub>i</sub> < A<sub>i+1</sub>, the temperature of the wind decreases by S degrees per altitude.</li>
	<li>If A<sub>i</sub> ≧ A<sub>i+1</sub>, the temperature of the wind increases by T degrees per altitude.</li>
</ul>

<p>The tectonic movement is active in the land of the Kingdom of IOI. You have the data of tectonic movements for Q days. In the j-th (1 ≤  j ≤ Q) day, the change of the altitude of Spot k for L<sub>j</sub> ≤ k ≤ R<sub>j</sub> (1 ≤ L<sub>j </sub>≤ R<sub>j</sub> ≤ N) is described by X<sub>j</sub>. If X<sub>j</sub> is not negative, the altitude increases by X<sub>j</sub>. If X<sub>j </sub>is negative, the altitude decreases by |X<sub>j</sub>|.</p>

<p>Your task is to calculate the temperature of the wind at the house of Mr. JOI after each tectonic movement.</p>

<p>Given the data of tectonic movements, write a program which calculates, for each j (1 ≤ j ≤ Q), the temperature of the wind at the house of Mr. JOI after the tectonic movement on the j-th day.</p>

### 입력 

 <p>Read the following data from the standard input.</p>

<ul>
	<li>The first line of input contains four space separated integers N; Q; S; T. This means there is a house of Mr. JOI at Spot N, there are Q tectonic movements, the temperature of the wind decreases by S degrees per altitude if the altitude increases, and the temperature of the wind increases by T degrees per altitude if the altitude decreases.</li>
	<li>The i-th line (1 ≤ i ≤ N +1) of the following N +1 lines contains an integer A<sub>i-1</sub>, which is the initial altitude at Spot (i - 1) before tectonic movements.</li>
	<li>The j-th line (1 ≤ j ≤ Q) of the following Q lines contains three space separated integers L<sub>j</sub>; R<sub><span style="font-size:small">j</span></sub>; X<sub><span style="font-size:small">j</span></sub>. This means, for the tectonic movement on the j-th day, the change of the altitude at the spots from L<sub><span style="font-size:small">j</span></sub> to R<sub><span style="font-size:small">j</span></sub> is described by X<sub><span style="font-size:small">j</span></sub>.</li>
</ul>

### 출력 

 <p>Write Q lines to the standard output. The j-th line (1 ≤ j ≤ Q) of output contains the temperature of the wind at the house of Mr. JOI after the tectonic movement on the j-th day.</p>

