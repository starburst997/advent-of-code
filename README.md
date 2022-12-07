# Advent of Code

My solutions to [Advent of Code](https://adventofcode.com/), started in 2022 but I had fun doing those little puzzles so I worked my way backward to previous years as well.

Using C++ and ~Visual Studio~ [Rider](https://www.jetbrains.com/rider/) *(didn't notice Rider support C++ as well now w/ Unreal)* since it has been a while since I used C++.

I've tried to use an optimized yet simple approach while still focusing on readability. No 3rd party library. Single, self-contained file. Trying different variations to explore C++ more.

You won't see functional stuff like this:

```C#
input.Split("\n").Select(line => line.Chunk(line.Length/2)).Select(GetCommonItemPriority).Sum();
```

<!--*While some might argue that this is "clean code", they run at awful speed and generate tons of alloc, I'm really surprised to see how popular they are being used, no wonder software keeps getting slower despite faster machines*-->

I'm trying to keep things running at `O(log n)` here, at the very least!

Please feel free to [point out](https://github.com/starburst997/advent-of-code/issues) any optimization that could've been used or different ways I could've approach a problem to run it faster. I *love* to improve, this is somewhat a training exercise as well.

`TODO: Add non-visual-studio way to build for other platforms`