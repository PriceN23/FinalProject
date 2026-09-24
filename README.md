# Final Project: Default Proposal
Nicholas Price & Troy Poniewaz <br/>
CompSci 222-01 <br/>
05/07/2025 <br/>

### Description
A program similar to multimedia players such as iTunes, Spotify, etc.
The program will not necessarily play audio or video, but rather help the user manage a library of related content.
The content can be based on real media or entirely fictional.
There must be enough content in the dataset to make viable queries.

## Minimum Viable Product
1. Create a single database file which includes entries for at least 8 tracks, 8 audio books, and 8 TV episodes.
2. At least two of each type of item (Track, Audio Book, TV Episode) should have the same creator.
3. At least 4 different creators are represented for each type of item.
4. Database correctly reads into the program from an external file and data is parsed into the most appropriate type for each field.
5. Menu functionality.
	1. Print out all entries in the database.
	2. Print out only the Tracks.
	3. Print out only the Audio Books.
	4. Print out only the TV Episodes.
	5. Print out all entries with a given creator.
	6. Sort all entries by their rating in descending order.
	7. Sort all entries in ascending order based on their year.
	8. Sort all entries by the lexicographical order of their title.
	9. Print out all entries released on or after a given year.
	10. Quit.
6. Program loops until the user selects the quit option from the main menu.
7. Entire program compiles and runs as expected to completion without any unhandled exceptions.
8. Protection against a malicious user attempting to break the program.

## Stretch Goals
1. Allow the user to add a new entry to the database. Also updates the orignal database file.
2. Allow the user to remove an entry from the database. Also updates the original databse file.
3. Allow the user to retrieve a ‘shuffled’ collection of all the music tracks in the database. Print this collection out and ensure the order is different every time.

## How to run
Download the FinalProject.zip <br/>
Unzip the file <br/>
Run Visual Studio <br/>
Select "Open a Project or Solution" <br/>
Select FinalProject.sln within folders <br/>

#### Files
finalProjectMain.cpp, data.h, baseData.h, baseData.cpp, track.h, track.cpp, audioBook.h, audioBook.cpp, tvEpisode.h, tvEpisode.cpp, 
README.md, FinalProject.sln, FinalProject.vcxproj, FinalProject.vcxproj.filters, .gitattributes, & .gitignore
