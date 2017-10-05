import Control.Applicative
import Control.Monad
import System.IO

solve num = (x + x + (n - 1) * 15 * c) * n `div` 2 + sum (map (+ (15 * n)) (takeWhile (< r) l))
    where l = [3, 6, 5, 9, 10, 12, 15]
          x = sum l
          c = length l
          n = num `div` 15
          r = num `mod` 15

main :: IO ()
main = do
    t_temp <- getLine
    let t = read t_temp :: Int
    forM_ [1..t] $ \a0  -> do
        n_temp <- getLine
        let n = read n_temp :: Int
        putStrLn $ show . solve $ n


getMultipleLines :: Int -> IO [String]

getMultipleLines n
    | n <= 0 = return []
    | otherwise = do          
        x <- getLine         
        xs <- getMultipleLines (n-1)    
        let ret = (x:xs)    
        return ret          

