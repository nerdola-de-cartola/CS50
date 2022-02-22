SELECT people.name FROM people
JOIN stars ON people.id = stars.person_id
JOIN movies ON movies.id = stars.movie_id
    WHERE NOT (people.name = "Kevin Bacon" AND people.birth = 1958) AND movies.id IN (
        SELECT movies.id FROM movies
        JOIN stars ON movies.id = stars.movie_id
        JOIN people ON people.id = stars.person_id
            WHERE people.name = "Kevin Bacon" AND people.birth = 1958
    )
    GROUP BY people.name