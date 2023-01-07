/*
Number of movies with an IMDb rating of 10.0.
Output: table with a single column and a single row (not counting the header) containing the number of movies with a 10.0 rating.
*/
SELECT count(rating) FROM ratings WHERE rating = 10.0;