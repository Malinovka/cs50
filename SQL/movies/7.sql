SELECT title, rating FROM movies, ratings WHERE year = 2010 AND movies.id = ratings.movie_id AND rating != 0 ORDER BY rating DESC, title;