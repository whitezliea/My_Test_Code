show DATABASES;

CREATE DATABASE CloudPan;

CREATE DATABASE FTP;

USE CloudPan;
DROP TABLE pan_user;
CREATE TABLE IF NOT EXISTS `pan_user`(
    `user_id` INT UNSIGNED AUTO_INCREMENT,
    `user_name` VARCHAR(100) NOT NULL,
    `user_passwd` VARCHAR(20) NOT NULL,
    `create_date` DATE,
     PRIMARY KEY(`user_id`)
)ENGINE=InnoDB DEFAULT CHARSET=utf8;

USE CloudPan;SELECT * FROM pan_user;

INSERT INTO pan_user
(user_name,user_passwd,create_date)
VALUES
("user2","passwd2",NOW());

select exists(select *from pan_user where user_name='user1' and user_passwd='passwd1');

UPDATE pan_user SET
user_file_id = "readme.txt" WHERE user_id = 1;




# gcc -o db_test MyDB.cpp -L/usr/lib/mysql -lmysqlclient -lstdc++
