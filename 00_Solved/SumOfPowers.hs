import Control.Applicative

recur :: Int -> [Int] -> Int
recur 0 _ = 1
recur _ [] = 0
recur n xs =
    let ns = map ((-) n) xs
        xss = (map (\x -> filter (> x)) $ takeWhile (<= n) xs) <*> [xs]  -- this one is faster than the following line
        --xss = map (\x -> filter (> x) $ takeWhile (<= n) xs) xs
    in sum $ zipWith (\a b -> recur a b) ns xss
        
solve :: Int -> Int -> Int
solve n p = recur n $ takeWhile (<= n) $ map (^ p) [1..n]
-- Alternative way:
-- solve n p = recur n $ takeWhile (<= n) $ [x ^ p | x <- [1..]]

main = do
    contents <- getContents
    let (n:p:_) = (map read $ lines contents)::[Int]
    putStrLn . show $ solve n p
