import React, { useContext, useState } from "react";
import {
  BarSongTitle,
  BottomBar,
  Button,
  PlayList,
  Song,
  SongTitle,
} from "./styles.js";
import { songList } from "./constants.js";

const buttonLabels = ["Not replaying", "Replaying all", "Replaying one"];

const PlayerContext = React.createContext();

const PlayerProvider = ({ children }) => {
  const [currentSongIndex, setCurrentSongIndex] = useState(null);
  const [loopMode, setLoopMode] = useState(0); // 0: Not replaying, 1: Replaying all, 2: Replaying one

  const playNextSong = () => {
    if (currentSongIndex === null) return;

    // Replaying one 모드일 때 곡이 변경되지 않도록 함
    if (loopMode === 2) return;

    const isLastSong = currentSongIndex === songList.length - 1;
    if (isLastSong) {
      if (loopMode === 1) setCurrentSongIndex(0); // Replaying all
      else setCurrentSongIndex(null); // Not replaying
    } else {
      setCurrentSongIndex(currentSongIndex + 1);
    }
  };

  const playPreviousSong = () => {
    if (currentSongIndex === null) return;

    // Replaying one 모드일 때 곡이 변경되지 않도록 함
    if (loopMode === 2) return;

    const isFirstSong = currentSongIndex === 0;
    if (isFirstSong) {
      if (loopMode === 1) {
        // Replaying all 모드일 때 첫 곡에서 마지막 곡으로 이동
        setCurrentSongIndex(songList.length - 1);
      } else {
        // Not replaying 모드에서는 첫 곡에서 멈춤
        setCurrentSongIndex(0);
      }
    } else {
      // 이전 곡으로 이동
      setCurrentSongIndex(currentSongIndex - 1);
    }
  };

  const toggleLoopMode = () => {
    setLoopMode((prevMode) => (prevMode + 1) % buttonLabels.length);
  };

  return (
    <PlayerContext.Provider
      value={{
        currentSongIndex,
        setCurrentSongIndex,
        playNextSong,
        playPreviousSong,
        loopMode,
        toggleLoopMode,
      }}
    >
      {children}
    </PlayerContext.Provider>
  );
};

const usePlayerContext = () => {
  const context = useContext(PlayerContext);
  if (!context) {
    throw new Error("usePlayerContext must be used within a PlayerProvider");
  }
  return context;
};

const ControlBar = () => {
  const {
    currentSongIndex,
    playNextSong,
    playPreviousSong,
    loopMode,
    toggleLoopMode,
  } = usePlayerContext();

  const currentSong =
    currentSongIndex !== null ? songList[currentSongIndex] : null;
  const title = currentSong
    ? `${currentSong.author} - ${currentSong.title}`
    : "";

  return (
    <BottomBar>
      <BarSongTitle data-testid="barTitle">{title}</BarSongTitle>
      <div>
        <Button data-testid="previousButton" onClick={playPreviousSong}>
          Previous
        </Button>
        <Button data-testid="nextButton" onClick={playNextSong}>
          Next
        </Button>
        <Button data-testid="currentModeButton" onClick={toggleLoopMode}>
          {buttonLabels[loopMode]}
        </Button>
      </div>
    </BottomBar>
  );
};

const Songs = () => {
  const { currentSongIndex, setCurrentSongIndex } = usePlayerContext();

  return (
    <PlayList>
      {songList.map(({ title, author, id }, index) => (
        <Song key={id} onClick={() => setCurrentSongIndex(index)}>
          <SongTitle data-testid={id} active={currentSongIndex === index}>
            {title}
          </SongTitle>
          <p>{author}</p>
        </Song>
      ))}
    </PlayList>
  );
};

export { PlayerProvider, Songs, ControlBar };
