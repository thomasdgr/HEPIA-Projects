CREATE SCHEMA IF NOT EXISTS `covid` DEFAULT CHARACTER SET utf8;

USE `covid`;

CREATE TABLE IF NOT EXISTS `covid`.`Country` (
  `slug` VARCHAR(127) NOT NULL,
  `name` VARCHAR(127) NOT NULL,
  `size` INT UNSIGNED NOT NULL,
  `latitude` INT UNSIGNED NOT NULL,
  `longitude` INT UNSIGNED NOT NULL,
  `total_population` INT UNSIGNED NOT NULL,
  `initial_total_cases` INT UNSIGNED NOT NULL,
  `initial_total_active` INT UNSIGNED NOT NULL,
  `initial_total_deaths` INT UNSIGNED NOT NULL,
  PRIMARY KEY (`slug`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

CREATE TABLE IF NOT EXISTS `covid`.`Type` (
    `name` VARCHAR(127) NOT NULL,
    PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

CREATE TABLE IF NOT EXISTS `covid`.`Perk` (
  `id` INT UNSIGNED NOT NULL,
  `name` VARCHAR(127) NOT NULL,
  `description` VARCHAR(1023) NOT NULL,
  `price` INT UNSIGNED NOT NULL,
  `value` FLOAT UNSIGNED NOT NULL,
  `type` VARCHAR(127) NOT NULL,
  PRIMARY KEY (`id`),
  CONSTRAINT `perk_constraint`
    FOREIGN KEY (`type`) REFERENCES `covid`.`Type` (`name`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

CREATE TABLE IF NOT EXISTS `covid`.`Virus` (
    `id` INT UNSIGNED NOT NULL AUTO_INCREMENT,
    `infectivity` FLOAT NOT NULL DEFAULT 0.15,
    `lethality` FLOAT NOT NULL DEFAULT 0.05,
    `resistance` FLOAT NOT NULL DEFAULT 0.005,
    `player_name` VARCHAR(127) NOT NULL,
    `points` INT UNSIGNED NOT NULL DEFAULT 0,
    `cure_progress` FLOAT NOT NULL DEFAULT 0.0,
    `cure_impact` FLOAT NOT NULL DEFAULT 0.0,
    PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

CREATE TABLE IF NOT EXISTS `covid`.`Game` (
  `virus_id` INT UNSIGNED NOT NULL,
  `start_date` VARCHAR(1023) NOT NULL,
  `current_date` VARCHAR(1023) NOT NULL,
  PRIMARY KEY (`virus_id`),
  CONSTRAINT `virus_constraint`
    FOREIGN KEY (`virus_id`) REFERENCES `covid`.`Virus` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

CREATE TABLE IF NOT EXISTS `covid`.`State` (
  `game_id` INT UNSIGNED NOT NULL,
  `slug` VARCHAR(127) NOT NULL,
  `current_total_cases` INT UNSIGNED NOT NULL,
  `current_total_active` INT UNSIGNED NOT NULL,
  `current_total_deaths` INT UNSIGNED NOT NULL,
  `current_total_cured` INT UNSIGNED NOT NULL,
  PRIMARY KEY (`game_id`, `slug`),
  CONSTRAINT `countryState_game_id_constraint`
    FOREIGN KEY (`game_id`) REFERENCES `covid`.`Game` (`virus_id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `countryState_slug_constraint`
    FOREIGN KEY (`slug`) REFERENCES `covid`.`Country` (`slug`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

CREATE TABLE IF NOT EXISTS `covid`.`UnlockedPerk` (
  `perk_id` INT UNSIGNED NOT NULL,
  `virus` INT UNSIGNED NOT NULL,
  PRIMARY KEY (`perk_id`, `virus`),
  CONSTRAINT `unlocked_constraint_perk`
    FOREIGN KEY (`perk_id`)
    REFERENCES `covid`.`Perk` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `unlocked_constraint_virus`
    FOREIGN KEY (`virus`)
    REFERENCES `covid`.`Virus` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- procédure pour trouver l'infectivité du virus en fonction de son id (différent pour chaque partie)
DELIMITER $
CREATE PROCEDURE covid.totalInfectivity(IN id_virus INT UNSIGNED)
BEGIN
    SELECT SUM(Perk.value) FROM UnlockedPerk INNER JOIN Perk ON UnlockedPerk.perk_id = Perk.id WHERE Perk.type = 'infectivity' AND UnlockedPerk.virus = id_virus; 
END
$
DELIMITER ;

-- procédure pour trouver la léthalité du virus en fonction de son id (différent pour chaque partie)
DELIMITER $
CREATE PROCEDURE covid.totalLethality(IN id_virus INT UNSIGNED)
BEGIN
    SELECT SUM(Perk.value) FROM UnlockedPerk INNER JOIN Perk ON UnlockedPerk.perk_id = Perk.id WHERE Perk.type = 'lethality' AND UnlockedPerk.virus = id_virus; 
END
$
DELIMITER ;

-- procédure pour trouver la résistance du virus en fonction de son id (différent pour chaque partie)
DELIMITER $
CREATE PROCEDURE covid.totalResitance(IN id_virus INT UNSIGNED)
BEGIN
    SELECT SUM(Perk.value) FROM UnlockedPerk INNER JOIN Perk ON UnlockedPerk.perk_id = Perk.id WHERE Perk.type = 'resistance' AND UnlockedPerk.virus = id_virus; 
END
$
DELIMITER ;

-- -- trigger pour vérifier lors de la sauvegarde que les valeurs insérées pour chaque pays ne dépassent pas la population du pays
DELIMITER $
CREATE TRIGGER trigger_state BEFORE INSERT ON covid.State 
FOR EACH ROW 
BEGIN 
    DECLARE pop INTEGER; 
    SELECT total_population FROM Country WHERE Country.slug = new.slug INTO pop;
    IF new.current_total_cases > pop 
    THEN 
        signal sqlstate '45000' 
        set message_text = 'current total cases can not be greater than the total population of the country';
    END IF;
    IF new.current_total_active > pop
    THEN 
        signal sqlstate '45000'
        set message_text = 'current total actives can not be greater than the total population of the country';
    END IF;
    IF new.current_total_deaths > pop
    THEN 
        signal sqlstate '45000'
        set message_text = 'current total deaths can not be greater than the total population of the country';
    END IF;
END; 
$
DELIMITER ;

-- vue pour obtenir le nombre de cas guéris en fonction des autres paramètres du pays une fois la sauvegarde effectuée
CREATE VIEW totalRecovered AS
SELECT State.slug, State.current_total_cases - (State.current_total_active + State.current_total_deaths) FROM State;

-- vue pour obtenir le classement des pays les plus touchés par le covid à un instant t (d'après la dernière sauvegarde)
CREATE VIEW ranking AS
SELECT State.slug, (State.current_total_active / Country.total_population) AS proportion FROM State INNER JOIN Country ON State.slug = Country.slug ORDER BY proportion DESC, State.slug ASC;


START TRANSACTION;
USE `covid`;
INSERT INTO `Virus`(`infectivity`, `lethality`, `resistance`, `player_name`, `points`, `cure_progress`, `cure_impact`) 
        VALUES (0.15,0.05,0.005, "ThomasKek", 0,0.0,0.0);
INSERT INTO `Virus`(`infectivity`, `lethality`, `resistance`, `player_name`, `points`, `cure_progress` ,`cure_impact`) 
        VALUES (0.15,0.05,0.005, "Banatwan", 0,0.0,0.0);
INSERT INTO `Virus`(`infectivity`, `lethality`, `resistance`, `player_name`, `points`, `cure_progress`, `cure_impact`) 
        VALUES (0.15,0.05,0.005, "Amon-Gus", 0,0.0,0.0);
COMMIT;

START TRANSACTION;
USE `covid`;

INSERT INTO `Game`(`virus_id`, `start_date`, `current_date`) 
        VALUES (1,"2020-01-22","2020-01-22");
INSERT INTO `Game`(`virus_id`, `start_date`, `current_date`) 
        VALUES (2,"2020-01-22","2020-01-22");
INSERT INTO `Game`(`virus_id`, `start_date`, `current_date`) 
        VALUES (3,"2020-01-22","2020-01-22");
COMMIT;

START TRANSACTION;
USE `covid`;
-- Coutries
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('afghanistan', 'Afghanistan', 4,2696,734,38928346,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('albania', 'Albania', 1,2097,615,2845955,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('algeria', 'Algeria', 6,1872,830,44700000,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('angola', 'Angola', 5,2074,1450,32097671,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('argentina', 'Argentina', 4,1003,1825,45808747,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('armenia', 'Armenia', 1,2407,624,2967900,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('australia', 'Australia', 10,3641,1654,25766008,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('austria', 'Austria', 2,2025,519,8933346,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('azerbaijan', 'Azerbaijan', 2,2450,628,10122148,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('bangladesh', 'Bangladesh', 2,3043,884,170346646,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('belarus', 'Belarus', 3,2182,431,9408350,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('belgium', 'Belgium', 1,1907,473,11554449,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('belize', 'Belize', 1,633,991,419199,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('benin', 'Benin', 1,1864,1093,12506347,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('bhutan', 'Bhutan', 1,3038,829,756129,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('bolivia', 'Bolivia', 4,957,1517,11797257,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('bosnia-and-herzegovina', 'Bosnia and Herzegovina', 1,2068,571,3332593,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('botswana', 'Botswana', 3,2159,1603,2410338,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('brazil', 'Brazil', 9,1189,1426,212885676,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('bulgaria', 'Bulgaria', 1,2159,595,6951482,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('burkina-faso', 'Burkina Faso', 2,1813,1061,21510181,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('cambodia', 'Cambodia', 1,3259,1058,15552211,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('cameroon', 'Cameroon', 2,2000,1182,24348251,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('canada', 'Canada', 6,620,331,38389658,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('central-african-republic', 'Central African Republic', 2,2121,1148,5633412,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('chad', 'Chad', 3,2085,1016,16818391,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('chile', 'Chile', 2,908,1679,19678363,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('china', 'China', 9,3270,737,1407126680,1096,503,17);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('colombia', 'Colombia', 4,830,1198,51049498,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('congo-brazzaville', 'Congo (Brazzaville)', 2,2053,1260,5293070,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('congo-kinshasa', 'Congo (Kinshasa)', 4,2153,1296,105044646,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('costa-rica', 'Costa Rica', 1,678,1099,5163038,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('croatia', 'Croatia', 1,2048,547,4047200,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('cuba', 'Cuba', 2,783,920,11193470,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('cyprus', 'Cyprus', 1,2269,713,888005,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('czech-republic', 'Czech Republic', 2,2029,482,10707839,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('cote-divoire', 'Côte d''Ivoire', 2,1757,1139,27087732,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('denmark', 'Denmark', 1,1959,391,5840045,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('dominican-republic', 'Dominican Republic', 1,880,964,10535535,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('ecuador', 'Ecuador', 2,758,1276,17694000,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('egypt', 'Egypt', 3,2232,851,101637309,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('eritrea', 'Eritrea', 1,2353,1007,3601000,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('estonia', 'Estonia', 1,2150,352,1329460,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('ethiopia', 'Ethiopia', 3,2367,1128,117876000,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('fiji', 'Fiji', 1,4246,1533,898402,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('finland', 'Finland', 2,2146,298,5506902,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('france', 'France', 3,1881,535,67399000,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('gabon', 'Gabon', 2,1994,1266,2233272,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('georgia', 'Georgia', 1,2392,602,3716858,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('germany', 'Germany', 2,1968,466,83190556,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('ghana', 'Ghana', 2,1816,1139,30955202,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('greece', 'Greece', 2,2145,663,10718565,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('guatemala', 'Guatemala', 1,596,1020,17109746,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('guinea', 'Guinea', 1,1631,1018,12907395,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('guyana', 'Guyana', 1,1019,1162,743699,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('haiti', 'Haiti', 1,847,969,11743017,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('holy-see-vatican-city-state', 'Holy See (Vatican City State)', 1,2038,627,825,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('honduras', 'Honduras', 1,651,1027,9450711,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('hungary', 'Hungary', 1,2083,525,9731000,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('iceland', 'Iceland', 2,1666,269,368590,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('india', 'India', 5,2879,959,1374667917,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('indonesia', 'Indonesia', 3,3448,1344,270203917,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('iran', 'Iran, Islamic Republic of', 3,2554,753,84288662,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('iraq', 'Iraq', 2,2396,742,41190700,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('ireland', 'Ireland', 2,1762,437,4977400,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('israel', 'Israel', 1,2295,759,9325980,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('italy', 'Italy', 2,1980,557,59304696,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('japan', 'Japan', 3,3615,714,125620000,2,2,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('jordan', 'Jordan', 1,2328,769,10903520,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('kazakhstan', 'Kazakhstan', 4,2664,477,18890688,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('kenya', 'Kenya', 2,2354,1253,47564296,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('korea-south', 'Korea (South)', 1,3490,695,51824142,1,1,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('kyrgyzstan', 'Kyrgyzstan', 1,2789,610,6626800,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('lao-pdr', 'Lao PDR', 1,3222,947,7337783,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('latvia', 'Latvia', 1,2144,380,1891300,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('lebanon', 'Lebanon', 1,2305,729,6769000,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('lesotho', 'Lesotho', 1,2210,1720,2007201,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('liberia', 'Liberia', 1,1700,1160,4661010,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('libya', 'Libya', 3,2072,840,6959000,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('lithuania', 'Lithuania', 1,2131,403,2790044,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('luxembourg', 'Luxembourg', 1,1928,490,626108,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('madagascar', 'Madagascar', 3,2464,1583,26923353,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('malawi', 'Malawi', 1,2298,1465,18898441,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('malaysia', 'Malaysia', 2,3390,1339,32753870,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('maldives', 'Maldives', 1,2840,1248,383135,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('mali', 'Mali', 2,1808,972,20856000,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('malta', 'Malta', 1,2054,708,514564,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('marshall-islands', 'Marshall Islands', 1,4208,1230,54516,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('mauritania', 'Mauritania', 2,1697,963,4271197,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('mauritius', 'Mauritius', 1,2615,1572,1266030,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('mexico', 'Mexico', 3,473,926,126014024,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('moldova', 'Moldova', 1,2201,529,2640438,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('monaco', 'Monaco', 1,1922,584,38100,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('mongolia', 'Mongolia', 3,3109,532,3368119,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('morocco', 'Morocco', 2,1742,765,36195172,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('mozambique', 'Mozambique', 2,2343,1524,30832244,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('myanmar', 'Myanmar', 2,3128,924,55294979,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('namibia', 'Namibia', 2,2065,1604,2550226,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('nepal', 'Nepal', 2,2944,816,30378055,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('netherlands', 'Netherlands', 1,1917,447,17573881,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('new-zealand', 'New Zealand', 2,4042,1905,5121541,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('nicaragua', 'Nicaragua', 1,667,1054,6527691,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('niger', 'Niger', 3,1968,984,24112753,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('nigeria', 'Nigeria', 3,1930,1115,211401000,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('norway', 'Norway', 2,1947,312,5391369,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('oman', 'Oman', 2,2600,937,4489483,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('pakistan', 'Pakistan', 2,2733,826,225200000,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('panama', 'Panama', 1,735,1120,4278500,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('papua-new-guinea', 'Papua New Guinea', 2,3865,1349,9122994,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('paraguay', 'Paraguay', 2,1056,1616,7353038,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('peru', 'Peru', 3,783,1407,33035304,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('philippines', 'Philippines', 1,3533,1084,109975011,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('poland', 'Poland', 2,2078,448,38268000,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('portugal', 'Portugal', 1,1738,642,10295909,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('qatar', 'Qatar', 1,2521,863,2717360,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('romania', 'Romania', 2,2153,545,19317984,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('russia', 'Russian Federation', 8,2890,269,146238185,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('saudi-arabia', 'Saudi Arabia', 3,2429,889,34218169,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('senegal', 'Senegal', 1,1629,1017,17223497,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('serbia', 'Serbia', 1,2106,572,6926705,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('sierra-leone', 'Sierra Leone', 1,1667,1120,8297882,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('singapore', 'Singapore', 1,3262,1233,5685807,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('slovakia', 'Slovakia', 1,2079,502,5459781,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('slovenia', 'Slovenia', 1,2025,539,2111461,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('somalia', 'Somalia', 2,2462,1191,16360000,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('south-africa', 'South Africa', 3,2138,1749,59622350,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('south-sudan', 'South Sudan', 2,2246,1146,13249924,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('spain', 'Spain', 3,1803,639,47351567,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('sri-lanka', 'Sri Lanka', 1,2948,1150,21919000,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('sudan', 'Sudan', 3,2244,984,43318025,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('suriname', 'Suriname', 1,1066,1195,590100,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('swaziland', 'Swaziland', 1,2256,1671,1093238,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('sweden', 'Sweden', 2,2029,312,10380491,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('switzerland', 'Switzerland', 1,1952,526,8655100,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('syria', 'Syrian Arab Republic (Syria)', 1,2344,715,18276000,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('taiwan', 'Taiwan, Republic of China', 1,3456,889,23539588,1,1,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('tajikistan', 'Tajikistan', 1,2729,658,9313800,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('tanzania', 'Tanzania, United Republic of', 2,2291,1358,59441988,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('thailand', 'Thailand', 1,3207,1013,66624617,4,2,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('togo', 'Togo', 1,1847,1140,7886000,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('trinidad-and-tobago', 'Trinidad and Tobago', 1,1002,1055,1366725,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('tunisia', 'Tunisia', 2,1970,723,11708370,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('turkey', 'Turkey', 2,2287,647,83614362,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('uganda', 'Uganda', 1,2285,1231,42885900,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('united-arab-emirates', 'United Arab Emirates', 1,2568,888,9503738,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('united-kingdom', 'United Kingdom', 2,1837,436,66796807,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('united-states', 'United States of America', 6,544,653,331351624,1,1,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('uruguay', 'Uruguay', 1,1111,1772,3554915,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('uzbekistan', 'Uzbekistan', 1,2636,594,34756283,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('venezuela', 'Venezuela (Bolivarian Republic)', 2,932,1138,28705000,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('vietnam', 'Viet Nam', 1,3320,1060,97580000,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('yemen', 'Yemen', 2,2487,1012,30491000,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('zambia', 'Zambia', 2,2192,1488,18400556,0,0,0);
INSERT INTO `Country`(`slug`, `name`, `size`, `latitude`, `longitude`, `total_population`, `initial_total_cases`, `initial_total_active`, `initial_total_deaths`)
        VALUES ('zimbabwe', 'Zimbabwe', 1,2240,1561,15790716,0,0,0);
COMMIT;

-- TYPE
START TRANSACTION;
USE `covid`;
INSERT INTO `Type`(`name`) VALUES ('infectivity');
INSERT INTO `Type`(`name`) VALUES ('lethality');
INSERT INTO `Type`(`name`) VALUES ('resistance');
COMMIT;

-- PERKS
START TRANSACTION;
USE `covid`;
-- infectivity
INSERT INTO `Perk`(`id`, `name`, `description`, `price`, `value`, `type`)
        VALUES (0,'Blood I','Covid spreads through the blood',3,0.05,'infectivity');
INSERT INTO `Perk`(`id`, `name`, `description`, `price`, `value`, `type`)
        VALUES (1,'Blood II','Covid causes hemophilia',6,0.1,'infectivity');
INSERT INTO `Perk`(`id`, `name`, `description`, `price`, `value`, `type`)
        VALUES (2,'Blood III','Covid causes heavy internal damage',9,0.15,'infectivity');
INSERT INTO `Perk`(`id`, `name`, `description`, `price`, `value`, `type`)
        VALUES (3,'Animal I','Covid is spread by birds',3,0.05,'infectivity');
INSERT INTO `Perk`(`id`, `name`, `description`, `price`, `value`, `type`)
        VALUES (4,'Animal II','Covid spreads through livestock',6,0.1,'infectivity');
INSERT INTO `Perk`(`id`, `name`, `description`, `price`, `value`, `type`)
        VALUES (5,'Animal III','Covid is spread by mosquitoes',9,0.15,'infectivity');
INSERT INTO `Perk`(`id`, `name`, `description`, `price`, `value`, `type`)
        VALUES (6,'Air I','low transmission radius',4,0.05,'infectivity');
INSERT INTO `Perk`(`id`, `name`, `description`, `price`, `value`, `type`)
        VALUES (7,'Air II','medium transmission radius',7,0.1,'infectivity');
INSERT INTO `Perk`(`id`, `name`, `description`, `price`, `value`, `type`)
        VALUES (8,'Air III','high transmission radius',10,0.15,'infectivity');
INSERT INTO `Perk`(`id`, `name`, `description`, `price`, `value`, `type`)
        VALUES (9,'Water I','Covid adapts partialy to tropical environments',4,0.05,'infectivity');
INSERT INTO `Perk`(`id`, `name`, `description`, `price`, `value`, `type`)
        VALUES (10,'Water II','Covid easily adapts to tropical environments',7,0.1,'infectivity');
INSERT INTO `Perk`(`id`, `name`, `description`, `price`, `value`, `type`)
        VALUES (11,'Water III','Covid spreads in drinking water',10,0.15,'infectivity');
-- lethality
INSERT INTO `Perk`(`id`, `name`, `description`, `price`, `value`, `type`)
        VALUES (12,'Nausea I','Vomiting increased',3,0.05,'lethality');
INSERT INTO `Perk`(`id`, `name`, `description`, `price`, `value`, `type`)
        VALUES (13,'Nausea II','Dehydration increased (more efficient in arid countries)',6,0.1,'lethality');
INSERT INTO `Perk`(`id`, `name`, `description`, `price`, `value`, `type`)
        VALUES (14,'Nausea III','Fatal infections',9,0.2,'lethality');
INSERT INTO `Perk`(`id`, `name`, `description`, `price`, `value`, `type`)
        VALUES (15,'Cough I','More efficient if air transmission increased',3,0.05,'lethality');
INSERT INTO `Perk`(`id`, `name`, `description`, `price`, `value`, `type`)
        VALUES (16,'Cough II','Population in cold countries very susceptible to pneumonia',6,0.1,'lethality');
INSERT INTO `Perk`(`id`, `name`, `description`, `price`, `value`, `type`)
        VALUES (17,'Cough III','Immune suppression and pulmonary edema',9,0.2,'lethality');
INSERT INTO `Perk`(`id`, `name`, `description`, `price`, `value`, `type`)
        VALUES (18,'Anemia I','More efficient if blood transmission increased',4,0.05,'lethality');
INSERT INTO `Perk`(`id`, `name`, `description`, `price`, `value`, `type`)
        VALUES (19,'Anemia II','Cells break down',7,0.1,'lethality');
INSERT INTO `Perk`(`id`, `name`, `description`, `price`, `value`, `type`)
        VALUES (20,'Anemia III','The body is deprived of oxygen, causing unconsciousness and death',10,0.2,'lethality');
INSERT INTO `Perk`(`id`, `name`, `description`, `price`, `value`, `type`)
        VALUES (21,'Insomnia I','Paranoia: Humans are less likely to receive the cure',4,0.05,'lethality');
INSERT INTO `Perk`(`id`, `name`, `description`, `price`, `value`, `type`)
        VALUES (22,'Insomnia II','Humans behave irrationally',7,0.1,'lethality');
INSERT INTO `Perk`(`id`, `name`, `description`, `price`, `value`, `type`)
        VALUES (23,'Insomnia III','Humans sink into madness',10,0.2,'lethality');
-- restitance
INSERT INTO `Perk`(`id`, `name`, `description`, `price`, `value`, `type`)
        VALUES (24,'Bacterial resistance I','Covid is more resistant to other bacteria',3,0.02,'resistance');
INSERT INTO `Perk`(`id`, `name`, `description`, `price`, `value`, `type`)
        VALUES (25,'Bacterial resistance II','Covid is more resistant in all environments',6,0.05,'resistance');
INSERT INTO `Perk`(`id`, `name`, `description`, `price`, `value`, `type`)
        VALUES (26,'Bacterial resistance III','Covid is powerfull',9,0.1,'resistance');
INSERT INTO `Perk`(`id`, `name`, `description`, `price`, `value`, `type`)
        VALUES (27,'Drug resistance I','Covid is more resistant to simple drugs',3,0.02,'resistance');
INSERT INTO `Perk`(`id`, `name`, `description`, `price`, `value`, `type`)
        VALUES (28,'Drug resistance II','Simple drugs no longer have an effect on covid',6,0.05,'resistance');
INSERT INTO `Perk`(`id`, `name`, `description`, `price`, `value`, `type`)
        VALUES (29,'Drug resistance III','Covids effct are only reduced with morphine',9,0.1,'resistance');
INSERT INTO `Perk`(`id`, `name`, `description`, `price`, `value`, `type`)
        VALUES (30,'Vaccine resistance I','Vaccine is difficult to create',4,0.02,'resistance');
INSERT INTO `Perk`(`id`, `name`, `description`, `price`, `value`, `type`)
        VALUES (31,'Vaccine resistance II','Vaccine becomes harder to create',7,0.05,'resistance');
INSERT INTO `Perk`(`id`, `name`, `description`, `price`, `value`, `type`)
        VALUES (32,'Vaccine resistance III','Vaccine becomes very hard to create',10,0.1,'resistance');
INSERT INTO `Perk`(`id`, `name`, `description`, `price`, `value`, `type`)
        VALUES (33,'Mutation I','Covid can mutate',4,0.02,'resistance');
INSERT INTO `Perk`(`id`, `name`, `description`, `price`, `value`, `type`)
        VALUES (34,'Mutation II','Frequent mutations',7,0.05,'resistance');
INSERT INTO `Perk`(`id`, `name`, `description`, `price`, `value`, `type`)
        VALUES (35,'Mutation III','Mutations prevent an effective vaccine from being found',10,0.1,'resistance');
COMMIT;


