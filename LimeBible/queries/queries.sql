Query to get the chapters from the treeview (simple)

SELECT bible_kjv.id, bible_kjv.book, bible_kjv.cap, bible_kjv.verse, bible_kjv.line FROM bible_kjv, books WHERE books.name = 'Genesis' AND bible_kjv.book = books.abbr AND cap = 1 ORDER BY bible_kjv.verse ASC; 

alternate
SELECT bible_kjv.id, bible_kjv.book, bible_kjv.cap, bible_kjv.verse, bible_kjv.line
FROM bible_kjv INNER JOIN books ON (bible_kjv.book = books.abbr)
WHERE (books.name = 'Genesis' AND bible_kjv.cap = 23)
ORDER BY bible_kjv.verse ASC;

=============================


SELECT
    bible_kjv.id
    , bible_kjv.book
    , bible_kjv.cap
    , bible_kjv.verse
    , bible_kjv.line
FROM
    bible.books
    INNER JOIN bible_kjv 
        ON (books.abbr = bible_kjv.book)
WHERE (bible_kjv.line LIKE '%God%' AND (books.id >= 1 AND books.id <= 3));