

replaceN :: a -> Int -> [a] -> [a]
replaceN _ _ [] = []
replaceN new 0 (_:xs) = new:xs
replaceN new pos (x:xs) = x : (replaceN new (pos - 1) xs)

-- Not used in this program 
-- replaceXY :: a -> Int -> Int -> [[a]] -> [[a]]
-- replaceXY _ _ _ [] = []
-- replaceXY new x 0 (l:ls) = (replaceN new x l) : ls
-- replaceXY new x y (l:ls) = l : (replaceXY new x (y - 1) ls)

makeGrid row col = replicate row $ replicate col '_'

drawTree :: Int -> Int -> Int -> Int -> [String] -> [String]
drawTree _ 0 _ _ grid = grid
drawTree h n y x grid = draw_sub_tree (x - 2 ^ h) . draw_sub_tree (x + 2 ^ h) $ processed
    where (front, remain1) = splitAt y grid
          (pre_trunk, remain2) = splitAt (2 ^ h) remain1
          (pre_branch, end) = splitAt (2 ^ h) remain2
          trunk = map (replaceN '1' x) pre_trunk
          draw_branch origin delta = replaceN '1' (origin + delta) . replaceN '1' (origin - delta)
          branch = zipWith (\n str -> draw_branch x n str) [1..] pre_branch
          processed = front ++ trunk ++ branch ++ end
          draw_sub_tree = drawTree (h - 1) (n - 1) (y + 2 ^ (h + 1))

main = do
    n <- readLn :: IO Int
    mapM_ putStrLn . reverse . drawTree 4 n 0 49 $ makeGrid 63 100
