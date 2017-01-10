import System.Random
import System.Environment (getArgs)
import Control.Monad (replicateM, replicateM_)

chars = ['a' .. 'z'] ++ "          "

randChar :: IO Char
randChar = do
  r <- randomRIO (0, length chars - 1)
  return $ chars !! r

randString :: IO String
randString = do
  m <- randomRIO (50,100)
  replicateM m randChar

main :: IO ()
main = do
  g <- getStdGen
  args <- getArgs
  let n = read (args !! 0) :: Int
  replicateM_ n (do
    str <- randString
    putStrLn str )
