import Data.Bits (testBit)
import Control.Monad (forM_,forM)
--import Data.Vector ((!), generate)
import Data.Array ((!), listArray)

data Tree a = Empty | Node a (Tree a) (Tree a)

instance (Show a) => Show (Tree a) where
    show Empty = ""
    show (Node v Empty Empty) = (show v)
    show (Node v l r) = "(" ++ (show l) ++ " " ++ (show v) ++ " " ++ (show r) ++ ")"

value Empty = 0
value (Node x _ _) = x

splitTreeString :: String -> (String, Char, String)
splitTreeString text = body "" 0 0 text
    where
        body checked depth count (x:xs)
            | x == '(' = body (checked ++ [x]) (depth + 1) count xs
            | x == ')' = body (checked ++ [x]) (depth - 1) count xs
            | x == ' ' = body (checked ++ [x]) depth (if depth == 1 then (count+1) else count) xs
            | depth == 0 = ("", x, "")
            | depth == 1 && count == 1 = (tail . init $ checked, x, tail . init $ xs)
            | otherwise = body (checked ++ [x]) depth count xs

parseTree :: String -> Tree Int
parseTree "" = Empty
parseTree text = Node value left right
    where
        (rawLeft, rawValue, rawRight) = splitTreeString text
        value = if rawValue == 'X' then 1 else 0
        left = parseTree rawLeft
        right = parseTree rawRight

getNode :: String -> Tree Int -> String
getNode _ Empty = "."
getNode "" (Node x _ _) = if x == 0 then "." else "X"
getNode (x:xs) (Node _ left right) = if x == '<'
                                     then getNode xs left
                                     else getNode xs right

nextState :: Int -> Int -> Int -> Tree Int -> Tree Int -> Int
nextState rule parent v left right = if testBit rule index then 1 else 0 where
    index = parent * 8 + (value left) * 4 + v * 2 + (value right)

nextTree :: Int -> Tree Int -> Tree Int
nextTree rule oldTree = body rule oldTree 0 where
    body _ Empty _ = Empty
    body rule (Node v left right) parent = 
        Node (nextState rule parent v left right) (body rule left v) (body rule right v)

{-
    Brutal force.
-}
nthTree :: String -> Int -> Int -> Tree Int
nthTree rawText _ 0 = parseTree rawText
nthTree rawText rule n = nextTree rule (nthTree rawText rule (n-1))

{-
    This version uses DP algorithm. Far more faster!
-}
nthTree' :: String -> Int -> Int -> Int -> Tree Int
nthTree' rawText rule max_count n = v ! n where
    v = listArray (0, max_count + 1) $ map f [0..(max_count + 1)]
    f 0 = parseTree rawText
    f i = nextTree rule (v ! (i-1))

main = do
    rule <- fmap (read::String->Int) getLine
    rawTree <- getLine
    queries <- fmap (read::String->Int) getLine
    process <- forM [1..queries] (\_ -> do
        (x1:x2:_) <- fmap words getLine
        let step = (read x1)::Int
        let path = tail . init $ x2
        return (step, path))
    let commands = scanl1 (\accu (s, p) -> (fst accu + s, p)) process
    let max_count = maximum [x | (x, _) <- commands]
    forM commands (\(step, path) -> do
        putStrLn . getNode path . nthTree' rawTree rule max_count $ step)
