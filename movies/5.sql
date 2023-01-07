/*
Titles and release years of all Harry Potter movies, in chronological order.
Output: table with two columns, one for the title of each movie and one for the release year of each movie.
Assume that the title of all Harry Potter movies will begin with the words “Harry Potter”,
and that if a movie title begins with the words “Harry Potter”, it is a Harry Potter movie.
*/
SELECT title, year FROM movies WHERE instr(title, "Harry Potter") = 1 ORDER BY year ASC;