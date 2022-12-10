# Advent of Code

My solutions to [Advent of Code](https://adventofcode.com/), started in 2022 but I had fun doing those little puzzles so I worked my way backward to previous years as well. Reminded me a lot about when I played [EXAPUNKS](https://github.com/starburst997/EXAPUNKS) so I went with a similar mindset (restrict the language to bare-minimum and focus on cycles).

Using C++17 and ~Visual Studio~ [Rider](https://www.jetbrains.com/rider/) *(didn't notice Rider support C++ as well now w/ Unreal)* since last time I used C++ was a while ago.

I've tried to use an optimized yet simple approach while still focusing on readability. No 3rd party library. Single, self-contained file. Trying different variations to explore C++ more.

I'm trying to keep things running at `O(log n)` here at the very least! And no fancy string manipulation either beside reading the inputs line by line.

I'm not playing for the leaderboard (which is based on submitting the answer as fast as possible at midnight) but I might try at least once or twice to see just how fast people submit it (I'll probably switch to C# for that or even JS).

## 2022

| Day | Title            | Part 1 | Part 2 | AoC |
|-----|------------------|--------|--------|-----|
| 1  | Calorie Counting | [Source](2022/Day_01/Day_01.cpp) | [Source](2022/Day_01_Bonus/Day_01_Bonus.cpp) | [Link](https://adventofcode.com/2022/day/1) |
| 2  | Rock Paper Scissors | [Source](2022/Day_02/Day_02.cpp) | [Source](2022/Day_02_Bonus/Day_02_Bonus.cpp) | [Link](https://adventofcode.com/2022/day/2) |
| 3  | Rucksack Reorganization | [Source](2022/Day_03/Day_03.cpp) | [Source](2022/Day_03_Bonus/Day_03_Bonus.cpp) | [Link](https://adventofcode.com/2022/day/3) |
| 4  | Camp Cleanup | [Source](2022/Day_04/Day_04.cpp) | [Source](2022/Day_04_Bonus/Day_04_Bonus.cpp) | [Link](https://adventofcode.com/2022/day/4) |
| 5  | Supply Stacks | [Source](2022/Day_05/Day_05.cpp) | [Source](2022/Day_05_Bonus/Day_05_Bonus.cpp) | [Link](https://adventofcode.com/2022/day/5) |
| 6  | Tuning Trouble | [Source](2022/Day_06/Day_06.cpp) | [Source](2022/Day_06_Bonus/Day_06_Bonus.cpp) | [Link](https://adventofcode.com/2022/day/6) |
| 7  | No Space Left On Device | [Source](2022/Day_07/Day_07.cpp) | [Source](2022/Day_07_Bonus/Day_07_Bonus.cpp) | [Link](https://adventofcode.com/2022/day/7) |
| 8  | Treetop Tree House | [Source](2022/Day_08/Day_08.cpp) | [Source](2022/Day_08_Bonus/Day_08_Bonus.cpp) | [Link](https://adventofcode.com/2022/day/8) |
| 9  | Rope Bridge | [Source](2022/Day_09/Day_09.cpp) | [Source](2022/Day_09_Bonus/Day_09_Bonus.cpp) | [Link](https://adventofcode.com/2022/day/9) |
| 10 | Cathode-Ray Tube | [Source](2022/Day_10/Day_10.cpp) | [Source](2022/Day_10_Bonus/Day_10_Bonus.cpp) | [Link](https://adventofcode.com/2022/day/10) |

## 2021

| Day | Title            | Part 1 | Part 2 | AoC |
|-----|------------------|--------|--------|-----|
| 1  | Sonar Sweep | [Source](2021/Day_01/Day_01.cpp) | [Source](2021/Day_01_Bonus/Day_01_Bonus.cpp) | [Link](https://adventofcode.com/2021/day/1) |
| 2  | Dive | [Source](2021/Day_02/Day_02.cpp) | [Source](2021/Day_02_Bonus/Day_02_Bonus.cpp) | [Link](https://adventofcode.com/2021/day/2) |
| 3  | Binary Diagnostic | [Source](2021/Day_03/Day_03.cpp) | [Source](2021/Day_03_Bonus/Day_03_Bonus.cpp) | [Link](https://adventofcode.com/2021/day/3) |
| 4  | Giant Squid | [Source](2021/Day_04/Day_04.cpp) | [Source](2021/Day_04_Bonus/Day_04_Bonus.cpp) | [Link](https://adventofcode.com/2021/day/4) |
| 5  | Hydrothermal Venture | [Source](2021/Day_05/Day_05.cpp) | [Source](2021/Day_05_Bonus/Day_05_Bonus.cpp) | [Link](https://adventofcode.com/2021/day/5) |
| 6  | Lanternfish | [Source](2021/Day_06/Day_06.cpp) | [Source](2021/Day_06_Bonus/Day_06_Bonus.cpp) | [Link](https://adventofcode.com/2021/day/6) |
| 7  | The Treachery of Whales | [Source](2021/Day_07/Day_07.cpp) | [Source](2021/Day_07_Bonus/Day_07_Bonus.cpp) | [Link](https://adventofcode.com/2021/day/7) |
| 8  | Seven Segment Search | [Source](2021/Day_08/Day_08.cpp) | [Source](2021/Day_08_Bonus/Day_08_Bonus.cpp) | [Link](https://adventofcode.com/2021/day/8) |
| 9  | Smoke Basin | [Source](2021/Day_09/Day_09.cpp) | [Source](2021/Day_09_Bonus/Day_09_Bonus.cpp) | [Link](https://adventofcode.com/2021/day/9) |
| 10 | Syntax Scoring | [Source](2021/Day_10/Day_10.cpp) | [Source](2021/Day_10_Bonus/Day_10_Bonus.cpp) | [Link](https://adventofcode.com/2021/day/10) |

<hr/>

I would love to see a mix of [Advent of Code](https://adventofcode.com/) and [EXAPUNKS](https://store.steampowered.com/app/716490/EXAPUNKS/) where the solutions are compiled and scored based on CPU cycles, memory, lines of code, etc. Grouped by language or global. Some inputs could be so big that careful parsing and memory management is needed, would spice things up.

Please feel free to [point out](https://github.com/starburst997/advent-of-code/issues) any optimization that could've been used or different ways I could've approach a problem to run it faster. I *love* to improve, this is somewhat a training exercise as well.

`TODO: Add non-visual-studio way to build for other platforms`