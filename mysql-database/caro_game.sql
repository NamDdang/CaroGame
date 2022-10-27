CREATE TABLE `user` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `username` varchar(100) NOT NULL UNIQUE,
  `password` varchar(20) NOT NULL,
  `win` int(11) NOT NULL,
  `lose` int(11) NOT NULL,
  `draw` int(11) NOT NULL,
  `online` BOOL NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

CREATE TABLE `match` (
  `matchId` int(11) NOT NULL AUTO_INCREMENT,
  `player1` varchar(100) NOT NULL,
  `player2` varchar(100) NOT NULL,
  `playerwin` varchar(100) NOT NULL,
  PRIMARY KEY (`matchId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
