/*
Average rating of all movies released in 2012.
YOutput: table with a single column and a single row (not counting the header) containing the average rating.
*/
SELECT avg(rating) FROM movies JOIN ratings ON movies.id = ratings.movie_id WHERE year = 2012;