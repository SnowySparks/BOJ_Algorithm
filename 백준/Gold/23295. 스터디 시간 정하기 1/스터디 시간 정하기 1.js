const input = require("fs")
  .readFileSync(process.platform === "linux" ? "/dev/stdin" : "./input.txt")
  .toString()
  .trim()
  .split("\n");

const MAXN = 10 ** 5 + 3;

const [N, T] = input[0].split(" ").map((item) => Number(item));
let maxTime = -1;
const preFix = Array.from(Array(MAXN), () => 0);
let lineIndex = 1;

const oneTime = [];

for (let i = 0; i < N; ++i) {
  const K = Number(input[lineIndex++]);
  for (let t = 0; t < K; ++t) {
    const [a, b] = input[lineIndex++].split(" ").map((item) => +item);
    maxTime = Math.max(b, maxTime);
    if (b - a === 1) {
      oneTime.push(a);
      continue;
    }
    preFix[a] += 1;
    preFix[b] -= 1;
  }
}

let maxValue = -1;
let [ansStart, ansEnd] = [0, 0];

for (let t = 1; t <= maxTime; ++t) {
  preFix[t] += preFix[t - 1];
}

oneTime.forEach((val) => {
  preFix[val] += 1;
});

for (let t = 1; t <= maxTime; ++t) {
  preFix[t] += preFix[t - 1];
}

for (let endT = T; endT <= maxTime; ++endT) {
  const cal = preFix[endT - 1] - (endT == T ? 0 : preFix[endT - T - 1]);
  if (maxValue < cal) {
    ansStart = endT - T;
    ansEnd = endT;
    maxValue = cal;
  }
}

console.log(ansStart, ansEnd);
