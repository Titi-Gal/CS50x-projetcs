/*
Titles of the five highest rated movies (in order) that Chadwick Boseman starred in, starting with the highest rated.
Output: table with a single column for the title of each movie.
Assume that there is only one person in the database with the name Chadwick Boseman.
*/
SELECT movies.title FROM
people JOIN stars ON people.id = stars.person_id
       JOIN movies ON stars.movie_id = movies.id
       JOIN ratings ON stars.movie_id = ratings.movie_id
WHERE people.name = "Chadwick Boseman"
ORDER BY ratings.rating DESC
LIMIT 5;