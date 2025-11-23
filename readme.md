# c-machine.c
[![](./docs/ts_114.png)](https://pasteboard.co/hZfdhHfhR396.jpg)

This is a specification of a computing machine directly specified (Godelized) in the C language.

It is a mathematical machine that can handle any form of CFG-like grammar.
It threads grammar rules as executable double-edged arrays.
It executes them and systematically explores all possible choices.

Think of it as a specified machine in hardware language, such as in C.

In assembly.
In instruction set architecture.
In the language of hardware/CPU.

Now, the instruction set architecture of the CPU is specified with the
language of the physical world, by transistors, by physics. Yes, it was first 
described in academic language as a [Turing machine](https://www.cs.virginia.edu/~robins/Turing_Paper_1936.pdf?now=%22to_see_definition_goto_page=3%22) - an α-machine.

So we have a machine within; We have two executors,
a nested machine architecture, the CPU, and the c-machine;
for that reason, the operational language for this two-headed
 unstoppable is written in two-edged arrays as executable pro-grammar rules.

The c-machine uses the call stack for backtracking, and we can actually
pinpoint exactly where that happens. Whenever you see two function calls
in a row, that’s where the stack grows, that’s the “gobbling up” part.
Everything else, the deeply nested single-call patterns, compiles down to
indirect jumps.

So the machine looks super-nested, but structurally it’s mostly flat with
a few deliberate points where the stack is used to explore alternatives.

# godel_copy.c
[![](./docs/ts_110.png)](./docs/ss_110.png)

It is a discrete mathematical object - a Turing machine with the
configuration of the [A-copy subroutine](https://en.wikipedia.org/wiki/Turing_machine_examples#A_copy_subroutine) expressed directly (Gödelized)
in a hardware language.

The Turing-machine tape is the o[1024] array, the head is s, and the transitions are encoded as pure control flow in C.

Mohamed Isham It’s a rare kind of implementation showing that we don’t need to
add accidental complexity when describing specifications in a systems language.
Most Turing-machine implementations use while(true) loops and transition tables,
which introduce branching and complexity.

Here the specification is the executable object — maybe a glimpse of
how academic writing could evolve when we learn to grow executable
languages that express problem-solution specifications directly.

