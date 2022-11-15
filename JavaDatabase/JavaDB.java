import java.sql.Connection;
import java.sql.DatabaseMetaData;  
import java.sql.DriverManager;  
import java.sql.SQLException;  
import java.sql.Statement;
import java.sql.ResultSet;
import java.sql.*;

public class DatabaseConnection
{
	public static Connection createDatabaseConnection(String databaseString)
	{	
		Connection dbConnection = null;	
	
		try
		{
			dbConnection = DriverManager.getConnection(databaseString);
		}

		catch(SQLException e)
		{
			System.out.println(e.getMessage());
		}
		
		return dbConnection;
	}
	
	public static void main(String[] args)
	{
		Connection dbConnection = createDatabaseConnection("jdbc:sqlite:Vocabulary.db");
		VocabularyList recordList = new VocabularyList();
		recordList.selectRecords(dbConnection,"SELECT * FROM VERB;");
	}
}

public class VocabularyList
{
	public void selectRecords(Connection dbConnection, String sqlStatementString)
	{
		try
		{
			Statement sqlStatementObject = dbConnection.createStatement();
			ResultSet result = sqlStatementObject.executeQuery(sqlStatementString);
		}

		catch(SQLException e)
		{
			System.out.println(e.getMessage());
		}
	}
}
