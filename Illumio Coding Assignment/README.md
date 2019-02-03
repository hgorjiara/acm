This is a challenge for Illumino!
Unfortunately, the project couldn't completely be finished in 90 mins.
The code is almost done, but it should be tested and make it running.
The Idea is the following, add all the valid rules to a set and each new packet
can be validated in O(1).
this approach is good for Firewall which can be fit in the memory and after loading it
we want to give response as quick as possible to requests!

Another approach, is just add rules to some sort of B-tree, in case rules doesn't fit
in to the memory, and each request would cost O(hight of the tree)

If I had more time, I would get the firewall working and write a generator to make 
a big input file and output file to automatically stress-test it. Also, I would come up
with a handcrafted test cases that I could check the edge cases!
