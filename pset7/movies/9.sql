SELECT DISTINCT name FROM
people JOIN stars JOIN movies ON movies.id = stars.movie_id AND people.id = stars.person_id
    WHERE movies.year = 2004
    ORDER BY people.birth;