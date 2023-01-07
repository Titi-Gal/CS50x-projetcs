/*
Titles of all movies in which both Johnny Depp and Helena Bonham Carter starred.
Output: table with a single column for the title of each movie.
Assume that there is only one person in the database with the name Johnny Depp.
Assume that there is only one person in the database with the name Helena Bonham Carter.
*/
SELECT movies.title FROM
people JOIN stars ON people.id = stars.person_id
       JOIN movies ON stars.movie_id = movies.id
WHERE people.name = "Johnny Depp" OR people.name = "Helena Bonham Carter"
GROUP BY movies.title HAVING count(movies.title) =2;