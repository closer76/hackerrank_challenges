
composeSubTree :: Int -> Int -> [String]
composeSubTree 0 _ = ["_"]
composeSubTree n x = ["_"]

replaceN :: a -> Int -> [a] -> [a]
replaceN _ _ [] = []
replaceN new 0 (_:xs) = new:xs
replaceN new pos (x:xs) = x : (replaceN new (pos - 1) xs)

replaceXY :: a -> Int -> Int -> [[a]] -> [[a]]
replaceXY _ _ _ [] = []
replaceXY new x 0 (l:ls) = (replaceN new x l) : ls
replaceXY new x y (l:ls) = l : (replaceXY new x (y - 1) ls)

makeGrid n = replicate n $ replicate n '-'

printGrid grid = mapM_ putStrLn grid

