SHOW DATABASES;

CREATE DATABASE test;

SHOW TABLES;


CREATE TABLE IF NOT EXISTS `test_tbl_2`(
   `test_id` INT UNSIGNED AUTO_INCREMENT,
   `test_title` VARCHAR(100) NOT NULL,
   `test_author` VARCHAR(40) NOT NULL,
   `submission_date` DATE,
   PRIMARY KEY ( `test_id` )
)ENGINE=InnoDB DEFAULT CHARSET=utf8;



USE test;
SELECT * FROM test_tbl_2;

DROP TABLE test_tbl;

DELETE FROM test_tbl_2 WHERE test_id =2;

INSERT INTO test_tbl_2 
      (test_title, test_author, submission_date)
      VALUES
      ("learn PHP", "runnoob", NOW());

INSERT INTO test_tbl_2
      (test_title, test_author, submission_date)
      VALUES
      ("learn MySQL", "hello world", '2020-04-28');  

INSERT INTO test_tbl_2
      (test_title, test_author, submission_date)
      VALUES
      ("JAVA guide", "test.COM", '2016-05-06');

FLUSH TABLES;