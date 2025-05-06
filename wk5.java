import org.openqa.selenium.By; 
import org.openqa.selenium.WebDriver; 
import org.openqa.selenium.WebElement; 
import org.openqa.selenium.chrome.ChromeDriver; 
public class Week5 { 
  public static void main(String[] args) throws InterruptedException { 
    System.setProperty("webdriver.chrome.driver", "F:\\Lab\\chromedriver\\chromedriver.exe"); 
    WebDriver driver=new ChromeDriver(); 
    driver.manage().window().maximize(); 
    driver.get("https://cmritautonomous.org/beeserp/Login.aspx"); 
    WebElement userName=driver.findElement(By.name("txtUserName")); 
    userName.sendKeys("20R01A05K6P"); 
    Thread.sleep(2000); 
    WebElement nxtBtn=driver.findElement(By.name("btnNext")); 
    nxtBtn.click(); 
    WebElement password=driver.findElement(By.name("txtPassword")); 
    password.sendKeys("20R01A05K6P"); 
    Thread.sleep(2000); 
    WebElement submit=driver.findElement(By.name("btnSubmit"));         
    submit.click(); 
  } 
} 
