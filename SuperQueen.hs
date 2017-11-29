{- Super-Queen on a Chessboard -}
{- URL: https://www.hackerrank.com/challenges/super-queens-on-a-chessboard/problem -}

filterOut :: [Int] -> Int -> [Int] -> [Int]
filterOut [] _ = id
filterOut (x:xs) level = filterOut xs (level+1) . f
    where f = if level == 1 || level == 2
              then filter (\a -> abs(a-x) > 2)
              else filter (\a -> a /= x && a /= (x + level) && a /= (x - level))

solve_body :: Int -> Int -> [Int] -> Int
solve_body size level [] = sum . map (solve_body size (level - 1)) . map (:[]) $ [1..size]
solve_body _ 0 _ = 1
solve_body size level queens = sum . map (solve_body size (level - 1)) . map (:queens) . filterOut queens 1 $ [1..size]

solve n = solve_body n n []

main = do
    num <- fmap (read::String->Int) getContents
    putStrLn . show $ solve num
