I strongly suggest getting the simplest insert and print done
before tackling remove.  You are allowed (expected) to keep
the trailing comma in place.

So, to get test1.in working correctly, It should produce:

Preorder = Kill Bill Volume 1, Die Hard, Terminator, 
Inorder = Die Hard, Kill Bill Volume 1, Terminator, 
Postorder = Die Hard, Terminator, Kill Bill Volume 1,

We can look at these orders and deduce that the tree looks like:
                 [     Kill Bill | - ]
               l=/              m=\            r=nullptr
         [ Die Hard | - ]    [ Terminator | - ]

When you start writing remove, then the
Tree::fix(Node*) method is where a lot of things happen.
You don't have to do all the cases right away!  Just start with the
simplest case (removing a key from a leaf) and work your way up.
Then work on the case where you can steal from a sibling...
Even if you don't get to the part where you have to merge, you'll
have a lot of points.
