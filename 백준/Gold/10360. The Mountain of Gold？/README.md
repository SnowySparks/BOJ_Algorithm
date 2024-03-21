# [Gold II] The Mountain of Gold? - 10360 

[문제 링크](https://www.acmicpc.net/problem/10360) 

### 성능 요약

메모리: 2340 KB, 시간: 108 ms

### 분류

벨만–포드, 그래프 이론, 최단 경로

### 제출 일자

2024년 3월 21일 10:37:35

### 문제 설명

<p>Ancient history and myth points to the Gunung Ledang (a.k.a. Ledang Mountain, as “gunung” is mountain in Malaysian) being the site of rich gold deposits, luring traders from as far as Greece and China. In the 14th Century, the Chinese seafarers plying the Straits of Melaka called it ‘Kim Sua’ meaning the ‘Golden Mountain’. The mountain was named ‘Gunung Ledang’, which means ‘mount from afar’, during the period of the Majapahit empire. Legend has it, that before the death of Princess Gunung Ledang, she hid a huge amount of gold far back in time during the creation of earth in Ledang Mountain. It is(apparently, becoming “was”) a mystery as to how the princess was able to go so far back in time. However, the princess was known to possess mystical powers that could enchant any pool she bath in into a portal that could manipulate time and space. A Malaysian historian of this time have discovered many of these pools located near many mountains around the world and named them “Ledang Pools”. A Ledang Pool is a portal through space and time connecting two pools. Ledang Pools have a few peculiar properties:</p>

<ul>
	<li>A Ledang Pool is a one way portal with two end points, i.e. it connects exactly two mountains.</li>
	<li>The time it takes to travel through a Ledang Pool is negligible.</li>
	<li>Each mountain might have multiple Ledang Pools’ end point in its area.</li>
	<li>For some unknown reasons, starting from Ledang Mountain in Malaysia, it is always possible to end up in any mountain (of course, which also has Ledang Pool end point)on earth by hopping a sequence of Ledang Pools.</li>
	<li>There are no Ledang Pools with both end points on the same mountain area.</li>
	<li>Each Ledang Pool has a fixed time difference (distortion) between their end points. For example, traveling through a certain Ledang Pool may cause that person to end up 42 years in the past at the other end point. It’s a space and time traveling!</li>
</ul>

<p>The Malaysian historian suspects that a large amount of gold is hidden in Ledang Mountain in the past because there’s no gold found in this mountain at this time (but then, where does the myth come from?). Starting from Ledang Mountain, the historian wants to reach the same mountain (Ledang Mountain) in the past. In order to this, he has to hop into two or more Ledang Pools, doing the space-and-time-travel things, and end up at Ledang Mountain in the past. Note that he does not care in which time in the past he will end up at Ledang Mountain as long as it is in the past. Your task is to help this historian to determine whether it is possible to reach Ledang Mountain in the past from Ledang Mountain in the present time by hopping a sequence of Ledang Pools.</p>

### 입력 

 <p>The input file starts with a line containing the number of cases T (1 ≤ T ≤ 20). Each case starts with two numbers N and M in a line. These indicate the number of mountains which have Ledang Pool end point (1 ≤ N ≤ 1,000) and the number of Ledang Pools (0 ≤ M ≤ 2,000). The pools are numbered from 0 (Ledang Mountain in Malaysia) up to N-1. The next M lines each contains three integers A, B, C (0 ≤ A, B < N; A ≠ B; -1,000 ≤ C ≤ 1,000) denoting the properties of one Ledang Pool, i.e. someone can do a space-time-travel from mountain A to mountain B and he will end up C year in the future/past. If C is positive, then it is in the future, otherwise it is in the past.</p>

### 출력 

 <p>For each case, output in a line "Case #X: Y" (without quotes) where X is the case number starting from 1, and Y is “possible” (without quotes) if it is indeed possible to reach Ledang Mountain in the past, otherwise output Y as “not possible” (without quotes).</p>

