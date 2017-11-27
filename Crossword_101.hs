import Data.List
import Data.Char

splitOn_body :: Char -> String -> [String] -> String -> [String]
splitOn_body _       ""   cur_list ""     = cur_list
splitOn_body pattern accu cur_list ""     = cur_list ++ [accu]
splitOn_body pattern accu cur_list (t:text)
    | t == pattern && accu == "" = splitOn_body pattern "" cur_list text
    | t == pattern               = splitOn_body pattern "" (cur_list ++ [accu]) text
    | otherwise                  = splitOn_body pattern (accu ++ [t]) cur_list text

splitOn pattern text = splitOn_body pattern "" [] text

groupFields = groupBy (\a b -> a == b || (a `elem` validChar && b `elem` validChar)) where validChar = '-':['A'..'Z']

canFill :: String -> String -> Bool
canFill word field
    | length field /= length word = False
    | otherwise = and $ zipWith (\x y -> x == '-' || x == y) field word

possibleRows_body :: String -> String -> [String] -> [String] -> [String]
possibleRows_body _ _ accu [] = filter (/= "") accu
possibleRows_body word passed accu (x:xs) =
    let newRow = if canFill word x then (passed ++ word ++ (concat xs)) else []
    in possibleRows_body word (passed ++ x) (newRow:accu) xs

possibleRows word row = possibleRows_body word "" [] $ groupFields row

possibleMatrix_body :: String -> [String] -> [[String]] -> [String] -> [[String]]
possibleMatrix_body _ _ accu [] = filter (/= []) accu
possibleMatrix_body word passed accu (x:xs) =
    let rows = possibleRows word x
        newMat = map (\row -> passed ++ [row] ++ xs) rows
    in possibleMatrix_body word (passed ++ [x]) (accu ++ newMat) xs

possibleMatrix word mat = possibleMatrix_body word [] [] mat

candMatrices word matrices = concat . map (possibleMatrix word) $ matrices

solve_body :: [String] -> [[String]] -> [[String]]
solve_body [] matrices = matrices
solve_body (w:ws) matrices = solve_body ws candidates
    where candidates = (candMatrices w matrices) ++ (map transpose . candMatrices w . map transpose $ matrices)

solve :: [String] -> [String] -> [String]
solve word_list matrix = result
    where (result:_) = solve_body word_list [matrix]

main = do
    contents <- getContents
    let lns = lines contents
    let mat = take 10 lns
    let phrases = splitOn ';' $ last lns
    putStrLn . unlines . solve phrases $ mat
