# [Silver I] File Fix-it (Small) - 12577 

[문제 링크](https://www.acmicpc.net/problem/12577) 

### 성능 요약

메모리: 3328 KB, 시간: 40 ms

### 분류

자료 구조, 해시를 사용한 집합과 맵, 문자열, 트리, 트리를 사용한 집합과 맵, 트라이

### 제출 일자

2024년 4월 16일 21:34:53

### 문제 설명

<p>On Unix computers, data is stored in <em>directories</em>. There is one <em>root directory</em>, and this might have several directories contained inside of it, each with different names. These directories might have even more directories contained inside of them, and so on.</p>

<p>A directory is uniquely identified by its name and its parent directory (the directory it is directly contained in). This is usually encoded in a <em>path</em>, which consists of several parts each preceded by a forward slash ('/'). The final part is the name of the directory, and everything else gives the path of its parent directory. For example, consider the path:</p>

<pre>/home/gcj/finals
</pre>

<p>This refers to the directory with name "finals" in the directory described by "/home/gcj", which in turn refers to the directory with name "gcj" in the directory described by the path "/home". In this path, there is only one part, which means it refers to the directory with the name "home" in the root directory.</p>

<p>To create a directory, you can use the <em>mkdir</em> command. You specify a path, and then <em>mkdir</em>will create the directory described by that path, but <em>only if</em> the parent directory already exists. For example, if you wanted to create the "/home/gcj/finals" and "/home/gcj/quals" directories from scratch, you would need four commands:</p>

<pre>mkdir /home
mkdir /home/gcj
mkdir /home/gcj/finals
mkdir /home/gcj/quals</pre>

<p>Given the full set of directories already existing on your computer, and a set of new directories you want to create if they do not already exist, how many <em>mkdir</em> commands do you need to use?</p>

### 입력 

 <p>The first line of the input gives the number of test cases, <strong>T</strong>. <strong>T</strong> test cases follow. Each case begins with a line containing two integers <strong>N</strong> and <strong>M</strong>, separated by a space.</p>

<p>The next <strong>N</strong> lines each give the path of one directory that already exists on your computer. This list will include every directory already on your computer other than the root directory. (The root directory is on every computer, so there is no need to list it explicitly.)</p>

<p>The next <strong>M</strong> lines each give the path of one directory that you want to create.</p>

<p>Each of the paths in the input is formatted as in the problem statement above. Specifically, a path consists of one or more lower-case alpha-numeric strings (i.e., strings containing only the symbols 'a'-'z' and '0'-'9'), each preceded by a single forward slash. These alpha-numeric strings are never empty.</p>

<h3>Limits</h3>

<ul>
	<li>1 ≤ <strong>T</strong> ≤ 100.</li>
	<li>No path will have more than 100 characters in it.</li>
	<li>No path will appear twice in the list of directories already on your computer, or in the list of directories you wish to create. A path may appear once in both lists however. (See example case #2 below).</li>
	<li>If a directory is listed as being on your computer, then its parent directory will also be listed, unless the parent is the root directory.</li>
	<li>The input file will be no longer than 100,000 bytes in total.</li>
	<li>0 ≤ <strong>N</strong> ≤ 10.</li>
	<li>1 ≤ <strong>M</strong> ≤ 10.</li>
</ul>

### 출력 

 <p>For each test case, output one line containing "Case #x: y", where x is the case number (starting from 1) and y is the number of <em>mkdir</em> you need.</p>

