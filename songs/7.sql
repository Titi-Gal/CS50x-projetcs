--average energy of songs that are by Drake
SELECT avg(songs.energy) FROM songs JOIN artists ON songs.artist_id = artists.id WHERE artists.name = "Drake";