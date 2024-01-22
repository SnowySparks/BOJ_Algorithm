# [Platinum IV] Airplane Parking - 5652 

[문제 링크](https://www.acmicpc.net/problem/5652) 

### 성능 요약

메모리: 3576 KB, 시간: 108 ms

### 분류

값 / 좌표 압축, 자료 구조, 다이나믹 프로그래밍, 정렬

### 제출 일자

2024년 1월 22일 16:35:52

### 문제 설명

<p>During this economic crisis time, Jack has started an incredible new business related to air travel, a parking-lot for airplane. He bought a very large land to park airplanes. However the land is very narrow, so that the only way airplanes can go in or go out of the parking lot must be in the Last-In First-Out fashion (see picture below). He only has spaces in the parking lot so he cannot take some airplane at the end out so that other airplanes can move.</p>

<p style="text-align: center;"><img alt="" src="" style="width: 347px; height: 68px;"></p>

<p>Because of the limitation of the parking lot, it is not possible to accommodate all requests for parking. Each request consists of the planned arrival time and planned departure time, which are the times the airplane arrives at the parking lot. An example below shows a request table for 4 planes.</p>

<table class="table table-bordered table-center-30 th-center td-center">
	<tbody>
		<tr>
			<th>Airplane</th>
			<th>Arrival</th>
			<th>Departure</th>
		</tr>
		<tr>
			<td>1</td>
			<td>1</td>
			<td>10</td>
		</tr>
		<tr>
			<td>2</td>
			<td>2</td>
			<td>5</td>
		</tr>
		<tr>
			<td>3</td>
			<td>3</td>
			<td>7</td>
		</tr>
		<tr>
			<td>4</td>
			<td>6</td>
			<td>9</td>
		</tr>
	</tbody>
</table>

<p>In this case, it is possible to accommodate airplane 1, 2, and 4. But it is not possible to accommodate both airplanes 2 and 3.</p>

<p>It is possible that different planes plan to arrive or depart the parking lot at the same time. Jack has the best crews working with him, so that they will manage to arrange the plane to the parking lot in the best way that if it is possible to park and take out the planes they will be able to do it. Consider another example.</p>

<table class="table table-bordered table-center-30 th-center td-center">
	<tbody>
		<tr>
			<th>Airplane</th>
			<th>Arrival</th>
			<th>Departure</th>
		</tr>
		<tr>
			<td>5</td>
			<td>10</td>
			<td>12</td>
		</tr>
		<tr>
			<td>6</td>
			<td>10</td>
			<td>15</td>
		</tr>
		<tr>
			<td>7</td>
			<td>13</td>
			<td>17</td>
		</tr>
	</tbody>
</table>

<p>Although airplane 5 and 6 arrive at the same time, Jack's crews know that airplane 5 will have to be out before airplane 6, so when both airplanes arrive they put airplane 6 in first, following by airplane 5.</p>

<p>Given a list of parking requests, you want to find the maximum number of airplanes that can be parked in this parking lot, provided that they can only depart in the Last-In First-Out fashion.</p>

### 입력 

 <p>The first line contains an integer T, the number of test cases (1 ≤ T ≤ 5). Each test case is in the following format.</p>

<p>The first line starts with an integer N (1 ≤ N ≤ 300) denoting the number of airplanes. The next N lines describe the request table. Each line 1 + i, for 1 ≤ i ≤ N, contains two integer S<sub>i</sub> and T<sub>i</sub>, (0 ≤ S<sub>i</sub> < T<sub>i</sub> ≤ 1,000,000,000) which are the planned arrival time and planned departing time for airplane i.</p>

### 출력 

 <p>For each test case, you program must output a single line consisting of one integer, the maximum number of airplanes that can be parked in Jack's parking lot.</p>

