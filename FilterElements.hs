import Control.Monad
import Data.List

formatListStr :: Show a => [a] -> String
formatListStr [] = "-1"
formatListStr [x] = show x
formatListStr (x:xs) = (show x) ++ " " ++ (formatListStr xs)

solve :: Int -> [Int] -> [Int]
solve threshold =
    map (\i -> fst i)
        . sortBy (\a b -> if snd a < snd b then LT else GT)
        . map head
        . filter (\g -> length g >= threshold)
        . groupBy (\a b -> fst a == fst b)
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
