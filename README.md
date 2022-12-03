# The Cherry Cake CLI

The CLI for a server-focused, interpreted and compiled programming language with simplicity, speed, and size in mind.

## Installation

You can install Cherry Cake by downloading any of the executables on the releases page. If there is not an executable for your platform, please make sure to create an issue on Github the name of your platform. 

If you are able to create an installation shortcut for Cherry Cake, please let us know by creating an issue and we will add it to the readme.

## Examples

### Hello World

The 'hello world' example is the most basic http-program that you can make in Cherry Cake. If you run this following code and visit [localhost:3000](http://localhost:3000/), you will see "Hello World".

```cherry

# Code inside runs when you go to '/'
get ~/ {

    # Responds with "Hello World"
    res.send("Hello World")

}

```

### Top-level Example

Top-level means that code in Cherry Cake does not need to be inside of a 'main' or 'start' function. This makes Cherry Cake a bit more flexible and simple than some traditional languages because it reduces the need to boilerplate code. But, Top-level programming can still be a bit tricky in Cherry Cake.
The following code will run immediately since there are no server endpoints in the below code. If there were endpoints, the code would wait for the server to initialize and then run the REPL code after. 

```cherry

# REPL Code runs immediately after the server is initialized
console.log("Hello World");
console.log(7 * 6); # prints 42

```

## License

The code in this project (the compiler, interpretter, tester and all other tools packaged with 'The Cherry Cake CLI') is licensed under the BSD four-clause license. The language itself (syntax, tokens, api, etc) is publicly available for general use, as all languages are. That being said, [The Fairfield Programming Association Inc.](https://about.fairfieldprogramming.org/) is the Benevolent Dictator for Life ([BDFL](https://en.wikipedia.org/wiki/Benevolent_dictator_for_life)), and manages a number of specifications to keep the language standardized across all implementations.  
