/*
Names of all people who starred in a movie released in 2004, ordered by birth year.
Output: table with a single column for the name of each person.
People with the same birth year are listed in any order.
People who have no birth year are listed in any order.
People who appeared in more than one movie in 2004 only appear once.
*/
SELECT DISTINCT people.name FROM
people JOIN stars ON people.id = stars.person_id
       JOIN movies ON stars.movie_id = movies.id
WHERE movies.year = 2004 ORDER BY people.birth;