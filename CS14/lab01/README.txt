This is assignment 1: Variations on a theme by Fibonacci. 

In the FibLoop function, I initialized the first two elements in the array to 0 and 1 and reset totalCalls and totalMoves to 1 and 0.
Then I used a for loop to output the rest of the sequence, while incrementing totalAdds.

The FibRec function is the most inefficient recursive function for Fibonacci. I set up two base cases and since this function returns the sum of the current and previous elements in the sequence, 
totalCalls is incremented by 2.

The FibRec1 function simply calls FibRec2, the helper function. I initialized oneBack and twoBack in this function, otherwise it would go out of scope and 
output an error. I am returning oneBack since we are trying to output the F(n). 

In FibRec2, to avoid creating duplicates, I created two temporary variables to be able to swap the elements in the sequence. 

For GenLoop, I created a for loop to iterate through the sequence n number of times. First, I multiplied the elements in the weights array by the 
elements in the inital array and stored the answer into a brand new array.
I hard coded the equation to add the elements in my brand new array as many times as k (e.g. if k = 2, I had the two numbers before the index). 
After, all the calculations, I output the last element in the sequence at the index of n.

For GenRec and GenRec2, I called GenRec2 in GenRec and returned back[n % k] because I want to return the value at the index of the array back.
Doing this is more efficient than shifting the values to the left. 

For part 6, I created a Fibnacci.cpp file, which included the class declaration and implementation. 

To compile my code, you would have to input g++ main.cpp Fibonacci.cpp