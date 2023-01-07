/*
Names of all people who have directed a movie that received a rating of at least 9.0.
Output: table with a single column for the name of each person.
Person directed more than one movie that received a rating of at least 9.0 only appear once.
*/

SELECT DISTINCT people.name FROM
people JOIN directors ON people.id = directors.person_id
       JOIN ratings ON directors.movie_id = ratings.movie_id
       WHERE ratings.rating >= 9.0;