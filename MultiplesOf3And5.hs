import Control.Applicative
import Control.Monad
import System.IO
import Data.Int

solve :: Int64 -> Int64
solve num = (x + x + (n - 1) * 15 * c) * n `div` 2 + sum (map (+ (15 * n)) (takeWhile (<= r) l))
    where l = [3, 5, 6, 9, 10, 12, 15]
          x = sum l
          c = fromIntegral (length l)
          n = (num - 1) `div` 15
          r = (num - 1) `mod` 15

main :: IO ()
main = do
    t_temp <- getLine
    let t = read t_temp :: Int
    forM_ [1..t] $ \a0  -> do
        n_temp <- getLine
        let n = read n_temp :: Int64
        putStrLn $ show . solve $ n


getMultipleLines :: Int -> IO [String]

getMultipleLines n
    | n <= 0 = return []
    | otherwise = do          
        x <- getLine         
        xs <- getMultipleLines (n-1)    
        let ret = (x:xs)    
        return ret          

