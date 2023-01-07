/*
Movies released in 2010 and their ratings, in descending order by rating. Movies with the same rating alphabetically by title.
Output: table with two columns, one for the title of each movie and one for the rating of each movie.
Movies without rating are not included.
*/
SELECT title, rating FROM movies JOIN ratings ON movies.id = ratings.movie_id WHERE year = 2010 ORDER BY rating DESC, title ASC;