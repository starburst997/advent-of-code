# Advent of Code

My solutions to [Advent of Code](https://adventofcode.com/), started in 2022 but I had fun doing those little puzzles so I worked my way backward to previous years as well. Reminded me a lot about when I played [EXAPUNKS](https://github.com/starburst997/EXAPUNKS) so I went with a similar mindset (restrict the language to bare-minimum and focus on cycles).

Using C++17 and ~Visual Studio~ [Rider](https://www.jetbrains.com/rider/) *(didn't notice Rider support C++ as well now w/ Unreal)* since it has been a while since I used C++.

I've tried to use an optimized yet simple approach while still focusing on readability. No 3rd party library. Single, self-contained file. Trying different variations to explore C++ more.

You won't see functional stuff like this:

```C#
input.Split("\n").Select(line => line.Chunk(line.Length/2)).Select(GetCommonItemPriority).Sum();
```

<!--*While some might argue that this is "clean code", they run at awful speed and generate tons of alloc, I'm really surprised to see how popular they are being used, no wonder software keeps getting slower despite faster machines*-->

I'm trying to keep things running at `O(log n)` here, at the very least! And no fancy string manipulation either beside reading the inputs line by line.

I'm not playing for the leaderboard (which is based on submitting the answer as fast as possible at midnight) but I might try at least once or twice to see just how fast people submit it (I'll probably switch to C# for that or even JS).

Please feel free to [point out](https://github.com/starburst997/advent-of-code/issues) any optimization that could've been used or different ways I could've approach a problem to run it faster. I *love* to improve, this is somewhat a training exercise as well.

`TODO: Add non-visual-studio way to build for other platforms`