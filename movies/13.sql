/*
Names of all people who starred in a movie in which Kevin Bacon born in 1958 also starred.
Output: table with a single column for the name of each person.
There may be multiple people named Kevin Bacon in the database.
Kevin Bacon himself should not be included in the resulting list.
*/
SELECT DISTINCT people.name FROM
stars JOIN people ON stars.person_id = people.id
WHERE stars.movie_id IN
    (SELECT movie_id FROM
    people JOIN stars ON people.id = stars.person_id
    WHERE people.name = "Kevin Bacon" AND people.birth = 1958)
AND people.name != "Kevin Bacon";