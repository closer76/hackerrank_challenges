import Data.Char

getSuperDigit :: Int -> Int
getSuperDigit num
    | num < 10  = num
    | otherwise = getSuperDigit . sum . map digitToInt . show $ num

main = do
    line <- getLine
    let (n:k:_) = words line
    let num = (sum . map digitToInt $ n) * (read k)
    putStrLn . show . getSuperDigit $ num
