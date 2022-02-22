CREATE SCHEMA IF NOT EXISTS `bdd` DEFAULT CHARACTER SET utf8;
USE `bdd`;

-- creation de la table Personne
CREATE TABLE IF NOT EXISTS `bdd`.`Personne`(
    `user_id` INT UNSIGNED NOT NULL DEFAULT 0,
    `nom` VARCHAR(127) NOT NULL,
    `prenom` VARCHAR(127) NOT NULL,
    `email` VARCHAR(127) NOT NULL,
    `telephone` VARCHAR(127) NOT NULL,
    PRIMARY KEY(`user_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- creation de la table Tag RFID
CREATE TABLE IF NOT EXISTS `bdd`.`TagRFID`(
    `tag_id` VARCHAR(127) NOT NULL DEFAULT "",
    PRIMARY KEY(`tag_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- creation de la table Possession
CREATE TABLE IF NOT EXISTS `bdd`.`Possession`(
    `user_id` INT UNSIGNED NOT NULL DEFAULT 0,
    `tag_id`  VARCHAR(127) NOT NULL,
    `date_validite` VARCHAR(127) NOT NULL,
    PRIMARY KEY(`user_id`, `date_validite`),
    CONSTRAINT `contrainte_personne`
        FOREIGN KEY(`user_id`) REFERENCES `bdd`.`Personne` (`user_id`)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
    CONSTRAINT `contrainte_tag`
        FOREIGN KEY(`tag_id`) REFERENCES `bdd`.`TagRFID` (`tag_id`)
        ON DELETE CASCADE
        ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- creation de la table Stand
CREATE TABLE IF NOT EXISTS `bdd`.`Stand`(
    `stand_id` INT UNSIGNED NOT NULL DEFAULT 0,
    `nom` VARCHAR(127) NOT NULL,
    `marque` VARCHAR(127) NOT NULL,
    PRIMARY KEY(`stand_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- creation de la table Présence Stand
CREATE TABLE IF NOT EXISTS `bdd`.`PresenceStand`(
    `tag_id`  VARCHAR(127) NOT NULL DEFAULT "",
    `stand_id` INT UNSIGNED NOT NULL DEFAULT 0,
    `temps_initial` VARCHAR(127) NOT NULL,
    `temps_final` VARCHAR(127) NOT NULL,
    PRIMARY KEY (`tag_id`, `stand_id`, `temps_initial`),
    CONSTRAINT `contrainte_tag_id`
        FOREIGN KEY(`tag_id`) REFERENCES `bdd`.`TagRFID` (`tag_id`)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
    CONSTRAINT `contrainte_stand`
        FOREIGN KEY(`stand_id`) REFERENCES `bdd`.`Stand` (`stand_id`)
        ON DELETE CASCADE
        ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- Personne
START TRANSACTION;
USE `bdd`;
INSERT INTO `bdd`.`Personne` (`user_id`, `nom`, `prenom`, `email`, `telephone`) VALUES (0, 'Dagier', 'Thomas', 'thomas.dagier@gmail.com', '0123456789');
INSERT INTO `bdd`.`Personne` (`user_id`, `nom`, `prenom`, `email`, `telephone`) VALUES (1, 'Rod', 'Quentin', 'quentin.rodrod@gmail.com', '9876543210');
INSERT INTO `bdd`.`Personne` (`user_id`, `nom`, `prenom`, `email`, `telephone`) VALUES (2, 'Perret', 'Xavier', 'xavier.perret@gmail.com', '0123498765');
INSERT INTO `bdd`.`Personne` (`user_id`, `nom`, `prenom`, `email`, `telephone`) VALUES (3, 'Paquito', 'Lemoustachu', 'ananas@gmail.com', '0123497766');
INSERT INTO `bdd`.`Personne` (`user_id`, `nom`, `prenom`, `email`, `telephone`) VALUES (4, 'Mire', 'Mire', 'cinque.heure@55.com', '0602555555');
COMMIT;

-- Tag RFID
START TRANSACTION;
USE `bdd`;
INSERT INTO `bdd`.`TagRFID` (`tag_id`) VALUES ("000000000000000000000075");
INSERT INTO `bdd`.`TagRFID` (`tag_id`) VALUES ("000000000000000000000076");
INSERT INTO `bdd`.`TagRFID` (`tag_id`) VALUES ("000000000000000000000077");
INSERT INTO `bdd`.`TagRFID` (`tag_id`) VALUES ("000000000000000000000078");
INSERT INTO `bdd`.`TagRFID` (`tag_id`) VALUES ("123030202039201750000000");
COMMIT;

-- Possession
-- 20 décembre 2021 à 23h59 et 59s
START TRANSACTION;
USE `bdd`;
INSERT INTO `bdd`.`Possession` (`user_id`, `tag_id`, `date_validite`) VALUES (0, "000000000000000000000075", '1640041199.000000');
INSERT INTO `bdd`.`Possession` (`user_id`, `tag_id`, `date_validite`) VALUES (1, "000000000000000000000076", '1640041199.000000');
INSERT INTO `bdd`.`Possession` (`user_id`, `tag_id`, `date_validite`) VALUES (2, "000000000000000000000077", '1640041199.000000');
INSERT INTO `bdd`.`Possession` (`user_id`, `tag_id`, `date_validite`) VALUES (3, "000000000000000000000078", '1640041199.000000');
INSERT INTO `bdd`.`Possession` (`user_id`, `tag_id`, `date_validite`) VALUES (4, "123030202039201750000000", '1640041199.000000');
COMMIT;

-- Stand
START TRANSACTION;
USE `bdd`;
INSERT INTO `bdd`.`Stand` (`stand_id`, `nom`, `marque`) VALUES (0, 'stand - Apple', 'Apple inc.');
INSERT INTO `bdd`.`Stand` (`stand_id`, `nom`, `marque`) VALUES (1, 'stand - Google', 'Google corp.');
INSERT INTO `bdd`.`Stand` (`stand_id`, `nom`, `marque`) VALUES (2, 'stand - Microsoft', 'Microsoft tm');
COMMIT;

-- Présence stand
-- Linux timestamp format
START TRANSACTION;
USE `bdd`;
INSERT INTO `bdd`.`PresenceStand` (`tag_id`,`stand_id`,`temps_initial`,`temps_final`) VALUES ("000000000000000000000075", 0, '1638882000.007800', '1638883800.000065');
INSERT INTO `bdd`.`PresenceStand` (`tag_id`,`stand_id`,`temps_initial`,`temps_final`) VALUES ("000000000000000000000076", 1, '1638885600.929100', '1638886215.210120');
INSERT INTO `bdd`.`PresenceStand` (`tag_id`,`stand_id`,`temps_initial`,`temps_final`) VALUES ("000000000000000000000077", 2, '1638894846.243311', '1638895387.000012');
INSERT INTO `bdd`.`PresenceStand` (`tag_id`,`stand_id`,`temps_initial`,`temps_final`) VALUES ("000000000000000000000078", 1, '1638874963.001400', '1638876213.102200');
COMMIT;
