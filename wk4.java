import java.util.HashMap; 
import org.openqa.selenium.By; 
import org.openqa.selenium.WebDriver; 
import org.openqa.selenium.WebElement; 
import org.openqa.selenium.chrome.ChromeDriver; 
import org.openqa.selenium.chrome.ChromeOptions; 
public class Week04 { 
  public static void main(String[] args) { 
    HashMap<String, Object> prefs=new HashMap<String, Object>(); 
    prefs.put("profile.default_content_setting_values.notifications",0); 
    ChromeOptions options=new ChromeOptions(); 
    options.setExperimentalOption("prefs", prefs); 
    System.setProperty("webdriver.chrome.driver","F:\\Lab\\chromedriver\\chromedriver.exe"); 
    WebDriver driver=new ChromeDriver(options); 
    driver.manage().window().maximize(); 
    driver.get("https://www.axisbank.com/"); 
    WebElement pop=driver.findElement(By.xpath("/html/body/div[1]/div[1]/div/span")); 
    pop.click(); 
  } 
}
