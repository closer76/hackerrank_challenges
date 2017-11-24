import Control.Monad
import Data.List

formatListStr :: Show a => [a] -> String
formatListStr [] = "-1"
formatListStr [x] = show x
formatListStr (x:xs) = (show x) ++ " " ++ (formatListStr xs)

-- O(n^2) solution...
{--
filterElem :: Int -> [Int] -> ([Int], [Int]) ->([Int], [Int])
filterElem _ [] (a, b) = (a, b)
filterElem expect (x:xs) (a, b)
    | expect == x = filterElem expect xs (x:a, b)
    | otherwise   = filterElem expect xs (a, b ++ [x])

solve :: Int -> [Int] -> [Int] -> [Int]
solve _ [] result = if result == [] then [-1] else result
solve k all@(x:xs) result = let
    (found, remain) = filterElem x all ([], [])
    new_result = if length found >= k
                 then result ++ [x]
                 else result
    in solve k remain new_result
--}

filterUnwanted :: Int -> Int -> [(Int, Int)] -> [(Int, Int)] -> [(Int, Int)]
filterUnwanted threshold count result input
    | input == []        = if count >= threshold then result else if result == [] then [] else ys
    | result == []       = filterUnwanted threshold 1 [x] xs
    | fst x == fst y     = filterUnwanted threshold (count + 1) result xs
    | count >= threshold = filterUnwanted threshold 1 (x:result) xs
    | otherwise          = filterUnwanted threshold 1 (x:ys) xs
    where
        (x:xs) = input
        (y:ys) = result

solve :: Int -> [Int] -> [Int]
solve threshold =
    map (\i -> fst i)
        . sortBy (\a b -> if snd a < snd b then LT else GT)
        . filterUnwanted threshold 0 []
        . sortBy (\a b -> if ((fst a) <= (fst b) && (snd a < snd b)) then LT else GT)
        . (flip zip) [1..]

main = do
    q <- readLn :: IO Int
    forM_ [1..q] $ \_ -> do
        line <- getLine
        let (n:k:_) = map (read::String->Int) . words $ line
        line <- getLine
        let input_seq = map (read::String->Int) . words $ line
        putStrLn . formatListStr . solve k $ input_seq
