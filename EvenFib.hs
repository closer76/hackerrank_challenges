import Control.Applicative
import Control.Monad
import System.IO

evenFib :: Int -> Int
evenFib 0 = 0
evenFib 1 = 2
evenFib n = 4 * evenFib (n - 1) + evenFib (n - 2)

main :: IO ()
main = do
    t_temp <- getLine
    let t = read t_temp :: Int
    forM_ [1..t] $ \a0  -> do
        n_temp <- getLine
        let n = read n_temp :: Int
        putStrLn $ show . sum . takeWhile (< n) $ [evenFib x | x <- [1..]]


getMultipleLines :: Int -> IO [String]

getMultipleLines n
    | n <= 0 = return []
    | otherwise = do          
        x <- getLine         
        xs <- getMultipleLines (n-1)    
        let ret = (x:xs)    
        return ret          


