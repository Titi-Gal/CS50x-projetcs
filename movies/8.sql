/*
Names of all people who starred in Toy Story.
Output: table with a single column for the name of each person.
Assume that there is only one movie in the database with the title Toy Story.
*/
SELECT people.name FROM
people JOIN stars ON people.id = stars.person_id
       JOIN movies ON stars.movie_id = movies.id
WHERE movies.title = "Toy Story";