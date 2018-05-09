{-# LANGUAGE ScopedTypeVariables #-}

module Main where

import qualified Data.ByteString     as BS
import           Data.Elf
import           Data.Monoid         ((<>))
import           Data.Word
import           Options.Applicative
import           System.Exit

main :: IO ()
main = do
  (Args filePath maxSize) <- execParser $
    info (argsParser <**> helper) fullDesc
  image <- BS.readFile filePath
  let elf = parseElf image
  if elfClass elf /= ELFCLASS32
    then do
      putStrLn "Can only identify 32bit ELF file."
      exitFailure
    else do
      let actualSize = memSize (elfSegments elf)
      if actualSize <= maxSize
        then putStrLn $
          "OK. " ++ show actualSize ++ " < " ++ show maxSize
        else do
          putStrLn $
            "Actual size " ++ show actualSize ++ " exceeds max size "
            ++ show maxSize
          exitFailure

data Args = Args
  { _filePath :: FilePath
  , _maxSize  :: Word32
  }

argsParser :: Parser Args
argsParser = Args
  <$> strOption
    ( long "file"
    <> metavar "FILE"
    <> help "Absolute path to the ELF (x86) file to check."
    )
  <*> option auto
    ( long "limit"
    <> metavar "LIMIT"
    <> help "Max size in bytes of the ELF image when loaded to MEMORY."
    )

memSize :: [ElfSegment] -> Word32
memSize [] = 0
memSize segments =
  let (beginAddress :: Word32) = fromIntegral $ elfSegmentVirtAddr (head segments)
      lastSegment = last segments
      (endAddress :: Word32) = fromIntegral $
        elfSegmentVirtAddr lastSegment + elfSegmentMemSize lastSegment
   in endAddress - beginAddress
