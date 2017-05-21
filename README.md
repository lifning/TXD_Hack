I found one of the first C programs I ever wrote (circa 2004) in an old backup and decided to upload it to GitHub, because evidently my instinct when I stumble upon something embarassing is to show the world.

Renderware games like Sonic Heroes had this texture archive format called .TXD, and I wanted to be able to modify the textures without copying the data in and out of these files by hand in a hex editor. So I instead learned how to program.

Almost every single line has a comment attached describing what it does in layman's terms. I guess you've gotta learn somehow!

Before making this Git repo, I made a cursory attempt to patch it up to build with g++ on amd64 (I originally wrote it in Visual C++ 6, I think), but didn't actually test the result on real files. It should compile with no args, just `g++ TXD_Hack.cpp` will do. It probably still works in MSVC as well.

